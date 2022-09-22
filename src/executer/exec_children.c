/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:17:45 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 17:43:53 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_pipe(t_data *data, t_exec_tool *tool)
{
	if (pipe(tool->pipe_fd) != 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, PIPE_ERR);
	}
}

static void handle_fork(t_data *data, t_exec_tool *tool)
{
	tool->fork_ret[tool->i] = fork();
	if (tool->fork_ret[tool->i] < 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, FORK_ERR);
	}
}

static void	redirect_to_pipe(t_data *data, t_exec_tool *tool)
{
	if (dup2(tool->pipe_fd[1], 1) < 0)
	{
		close(tool->pipe_fd[0]);
		close(tool->pipe_fd[1]);
		global_free(data, DUP_ERR);
	}
	if (close(tool->pipe_fd[0]) != 0)
	{
		close(tool->pipe_fd[1]);
		global_free(data, CLOSE_ERR);
	}
	if (close(tool->pipe_fd[1]) != 0)
		global_free(data, CLOSE_ERR);
}

static void exec_child(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char	**env_tab;

	create_child_signals();
	env_tab = NULL;
	if (!is_last_cmd(cmd))
		redirect_to_pipe(data, tool);
	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	if (((t_cmd_node *)cmd->content)->cmd_tab[0])
	{
		env_tab = get_env_tab(data);
		if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, true) != NO_ERR)
		{
			if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
			{
				ft_printf_fd("%s: command not found\n", 2, ((t_cmd_node *)cmd->content)->cmd_tab[0]);
				free_exec_tool(&tool);
				ft_free_tab(&env_tab);
				if (!is_err_redir_or_chevron_err(data))
				{
					ft_printf_fd("execve failed ? = %s\n", 2, get_expand_value(data, "?"));
					set_expand(data, "?", "127");
				}
				global_free(data, NO_ERR);
			}
		}
	}
	ft_free_tab(&env_tab);
	free_exec_tool(&tool);
	global_free(data, NO_ERR);
}

void	exec_children(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	int	lexer_len;

	lexer_len = 0;
	while (cmd)
	{
		tool->ret = open_and_set_fds(data->words, lexer_len, (t_cmd_node *)cmd->content);
		if (tool->ret == MALLOC_ERR)
		{
			free_exec_tool(&tool);
			global_free(data, tool->ret);
		}
		lexer_len = skip_node(data->words, lexer_len);
		handle_pipe(data, tool);
		cancel_parent_signals();
		handle_fork(data, tool);
		if (tool->fork_ret[tool->i] == 0)
			exec_child(data, cmd, tool);
		redirect_pipe_out(data, tool->pipe_fd);
		cmd = cmd->next;
		tool->i++;
	}
}
