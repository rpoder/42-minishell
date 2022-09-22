/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:17:45 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 01:35:13 by rpoder           ###   ########.fr       */
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

static void	set_expand_declarations_to_local(t_data *data, t_list *cmd)
{
	t_list	*expand_declaration;

	expand_declaration = ((t_cmd_node *)cmd->content)->expand_declarations;
	if (expand_declaration)
	{
		set_expand(data, ((t_expand *)expand_declaration->content)->key, ((t_expand *)expand_declaration->content)->value);
		expand_declaration = expand_declaration->next;
	}
}

static void exec_child(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char	**env_tab;

	env_tab = NULL;
	if (!is_last_cmd(cmd))
		redirect_to_pipe(data, tool);

	// set expand_declarations local_vars ici aussi
	// test_parser(data->cmds);
	// set_expand_declarations_to_local(data, cmd);
	// test_local_expands(data);
	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	if (((t_cmd_node *)cmd->content)->cmd_tab[0])
	{
		env_tab = get_env_tab(data);
		if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, true) != NO_ERR)
		{
			if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
			{
				ft_printf_fd("minilsshell: %s: command not found\n", 2, ((t_cmd_node *)cmd->content)->cmd_tab[0]);
				ft_free_tab(&env_tab);
				global_free(data, ERR_NOT_DEFINED);
			}
		}
	}
	free_exec_tool(&tool);
	global_free(data, NO_ERR);
}

void	exec_children(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	int	lexer_len;

	lexer_len = 0;
	while (cmd)
	{
		///////////////NORMER
		//set_fds
		tool->ret = open_and_set_fds(data->words, lexer_len, (t_cmd_node *)cmd->content);
		if (tool->ret != NO_ERR && tool->ret != OPEN_ERR) //PROTEGER
		{
			free_exec_tool(&tool);
			close(tool->fd_stdin);
			global_free(data, tool->ret);
		}
		//avance lexer a next node
		while (data->words[lexer_len] && data->words[lexer_len][0] != '|')
			lexer_len++;
		if (data->words[lexer_len])
			lexer_len++;
		////////////////////

		handle_pipe(data, tool);
		cancel_parent_signals();
		handle_fork(data, tool);
		// redirect et execute child
		if (tool->fork_ret[tool->i] == 0)
		{
			create_child_signals();
			exec_child(data, cmd, tool);
		}
		//redirect resultat de l'enfant
		redirect_pipe_out(data, tool->pipe_fd);
		cmd = cmd->next;
		tool->i++;
	}
}
