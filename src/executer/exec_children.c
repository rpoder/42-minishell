/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:17:45 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 15:02:20 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe(t_data *data, t_exec_tool *tool)
{
	if (pipe(tool->pipe_fd) != 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, pipe_err);
	}
}

static void	handle_fork(t_data *data, t_exec_tool *tool)
{
	tool->fork_ret[tool->i] = fork();
	if (tool->fork_ret[tool->i] < 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, fork_err);
	}
}

static void	redirect_to_pipe(t_data *data, t_exec_tool *tool)
{
	if (dup2(tool->pipe_fd[1], 1) < 0)
	{
		close(tool->pipe_fd[0]);
		close(tool->pipe_fd[1]);
		global_free(data, dup_err);
	}
	if (close(tool->pipe_fd[0]) != 0)
	{
		close(tool->pipe_fd[1]);
		global_free(data, close_err);
	}
	if (close(tool->pipe_fd[1]) != 0)
		global_free(data, close_err);
}

static void	exec_child(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = ((t_cmd_node *)cmd->content);
	default_all_sigs();
	if (!is_last_cmd(cmd))
		redirect_to_pipe(data, tool);
	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	free_exec_tool(&tool);
	if (cmd_node->cmd_tab[0])
	{
		if (exec_builtins(data, cmd_node->cmd_tab, true, tool) != no_err)
		{
			if (execve(cmd_node->path, cmd_node->cmd_tab,
					data->default_env) != 0)
			{
				ft_printf_fd("%s: command not found\n", 2, cmd_node->cmd_tab[0]);
				if (!is_redir_err_or_chevron_err(data))
					set_expand(data, "?", "127");
			}
		}
	}
	global_free(data, no_err);
}

void	exec_children(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	int	lexer_len;

	lexer_len = 0;
	while (cmd)
	{
		tool->ret = open_and_set_fds(data->words, lexer_len,
				(t_cmd_node *)cmd->content);
		if (tool->ret == malloc_err)
		{
			free_exec_tool(&tool);
			global_free(data, malloc_err);
		}
		else if (tool->ret == open_err)
			set_expand(data, "?", "1");
		lexer_len = skip_node(data->words, lexer_len);
		handle_pipe(data, tool);
		ignore_all_sigs();
		handle_fork(data, tool);
		if (tool->fork_ret[tool->i] == 0)
			exec_child(data, cmd, tool);
		redirect_pipe_out(data, tool->pipe_fd);
		cmd = cmd->next;
		tool->i++;
	}
}
