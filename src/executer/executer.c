/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/15 11:24:49 by margot           ###   ########.fr       */
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

int	execute_child(t_data *data, t_list *cmd, int *pipe_fd)
{
	char **env_tab;

	if (!is_last_cmd(cmd))
	{
		if (dup2(pipe_fd[1], 1) < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			global_free(data, DUP_ERR);
		}
	}
	if (close(pipe_fd[0]) != 0)
	{
			close(pipe_fd[1]);
			global_free(data, CLOSE_ERR);
	}
	if (close(pipe_fd[1]))
		global_free(data, CLOSE_ERR);

	chevron_redirection(data, (t_cmd_node *)cmd->content);
	env_tab = get_env_tab(data);
	if (!env_tab)
		global_free(data, MALLOC_ERR);
	// check if builtins
	if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
		global_free(data, ERR_NOT_DEFINED);
	return (0);
}

void	execute_cmds(t_data *data, t_list *cmd)
{
	t_exec_tool	*tool;
	int			i;
	int			j;

	i = 0;
	tool = init_tool(cmd);
	tool->fd_stdin = dup(0);
	if (tool->fd_stdin < 0)
		global_free(data, DUP_ERR);
	while(cmd)
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
			execute_child(data, cmd, tool->pipe_fd);
		redirect_pipe_out(data, tool->pipe_fd);
		cmd = cmd->next;
		i++;
	}
	if (wait_all_children(data, tool->fork_ret, i) != 0)
	{
		close(tool->fd_stdin);
		free(tool->fork_ret);
		global_free(data, WAITPID_ERR);
	}
	// recuperer err de l'enfant

	if (dup2(tool->fd_stdin, 0) < 0)
	{
		free(tool->fork_ret);
		close(tool->fd_stdin);
		global_free(data, DUP_ERR);
	}
	close(tool->fd_stdin);
}

void	executer(t_data *data)
{
	execute_cmds(data, data->cmds);
}

