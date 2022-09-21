/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/21 11:14:49 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all_children(t_data *data, pid_t *fork_ret, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (waitpid(fork_ret[j], NULL, 0) < 0)
			return (-1);
		j++;
	}
	return (0);
}

static void execute_child(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char **env_tab;

	ft_printf_fd("IN EXECUTE CHILD\n", 2);
	env_tab = NULL;
	if (!is_last_cmd(cmd))
	{
	if (dup2(tool->pipe_fd[1], 1) < 0)
		{
			close(tool->pipe_fd[0]);
			close(tool->pipe_fd[1]);
			global_free(data, DUP_ERR);
		}
	}
	if (close(tool->pipe_fd[0]) != 0)
	{
		close(tool->pipe_fd[1]);
		global_free(data, CLOSE_ERR);
	}
	if (close(tool->pipe_fd[1]))
		global_free(data, CLOSE_ERR);

	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);

	if (((t_cmd_node *)cmd->content)->cmd_tab[0])
	{
		env_tab = get_env_tab(data);
	/* 	if (!env_tab)
		{
			free_exec_tool(&tool);
			global_free(data, MALLOC_ERR);
		} */
		if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, true) != NO_ERR)
		{
			test_parser(data->cmds);
			if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
			{
				ft_free_tab(&env_tab);
				free_exec_tool(&tool);
				global_free(data, ERR_NOT_DEFINED);
			}
		}
	}
	free_exec_tool(&tool);
	global_free(data, NO_ERR);
}

void	exec_no_child_builtin(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char **env_tab;

	env_tab = get_env_tab(data);
	if (!env_tab)
	{
		free_exec_tool(&tool);
		global_free(data, MALLOC_ERR);
	}

	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, false) != NO_ERR)
	{
			ft_free_tab(&env_tab);
			free_exec_tool(&tool);
			global_free(data, ERR_NOT_DEFINED);
	}
	ft_free_tab(&env_tab);
}

void	execute_cmds(t_data *data, t_list *cmd)
{
	t_exec_tool	*tool;
	int			i;
	int			j;

	i = 0;
	tool = init_exec_tool(cmd);
	tool->fd_stdin = dup(0);
	if (tool->fd_stdin < 0)
	{
		free_exec_tool(&tool);
		global_free(data, DUP_ERR);
	}

	if (ft_lstlen(cmd) == 1 && is_builtin(((t_cmd_node *)cmd->content)->cmd_tab[0]) >= 0)
	{
		tool->fd_stdout = dup(1);
		if (tool->fd_stdout < 0)
		{
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
		exec_no_child_builtin(data, cmd , tool);
		if (dup2(tool->fd_stdout, 1) < 0)
		{
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
	}
	else
	{
		while (cmd)
		{
			//handle_pipe
			if (pipe(tool->pipe_fd) != 0)
			{
				close(tool->fd_stdin);
				global_free(data, PIPE_ERR);
			}

			//handle_fork
			tool->fork_ret[i] = fork();
			if (tool->fork_ret[i] < 0)
			{
				close(tool->fd_stdin);
				global_free(data, PIPE_ERR);
			}

			if (tool->fork_ret[i] == 0)
				execute_child(data, cmd, tool);
			redirect_pipe_out(data, tool->pipe_fd);
			cmd = cmd->next;
			i++;
		}
		if (wait_all_children(data, tool->fork_ret, i) != 0)
		{
			free_exec_tool(&tool);
			global_free(data, WAITPID_ERR);
		}
		// recuperer err de l'enfant

		if (dup2(tool->fd_stdin, 0) < 0)
		{
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
	}
	free_exec_tool(&tool);
}

void	executer(t_data *data)
{
	execute_cmds(data, data->cmds);
}

