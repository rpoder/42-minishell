/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/14 13:58:50 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_pipe(t_data *data)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		global_free(data, MALLOC_ERR);

	return(pipe_fd);
}

void	chevron_redirection(t_data *data, t_cmd_node *cmd)
{
	if (cmd->fd_in >= 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
}

int	execute_child(t_data *data, t_list *cmd, int *pipe_fd)
{
	char **env_tab;

	if (!is_last_cmd(cmd))
	{
		dup2(pipe_fd[1], 1);
/* 		if (dup2(pipe_fd[1], 1) != 0)
			return (PIPE_ERR); */
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	chevron_redirection(data, (t_cmd_node *)cmd->content);
	env_tab = get_env_tab(data);
	if (!env_tab)
		global_free(data, MALLOC_ERR);
	// check if builtins
	if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
		global_free(data, ERR_NOT_DEFINED);
	return (0);
}

void	redirect_pipe_out(t_data *data, int *pipe_fd)
{
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// if (dup2(pipe_fd[0], 0) != 0)
	// {
	// 	close(pipe_fd[0]);
	// 	close(pipe_fd[1]);
	// 	global_free(data, DUP_ERR);
	// }
	// if (close(pipe_fd[0]) != 0)
	// {
	// 	close(pipe_fd[1]);
	// 	global_free(data, DUP_ERR);
	// }
	// if (close(pipe_fd[1]) != 0)
	// 	global_free(data, DUP_ERR);
}

int	wait_all_children(t_data *data, pid_t *fork_ret, int i)
{
	int	j;

	j = 0;
	printf("i = %d\n", i);
	printf("forkret %p\n", fork_ret);
	while (j < i)
	{
		waitpid(fork_ret[j], NULL, 0);
		// {
		// 	printf("err on i = %d\n", i);
		// 	return (-1);
		// }
	//printf("coucou\n");
		j++;
	}
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
	while(cmd)
	{
		if (pipe(tool->pipe_fd) != 0)
		{
			close(tool->fd_stdin);
			global_free(data, PIPE_ERR);
		}

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
	printf("fork ret[0]%d\n", tool->fork_ret[0]);
	printf("fork ret[1]%d\n", tool->fork_ret[1]);
	printf("fork ret[2]%d\n", tool->fork_ret[2]);
	printf("fork ret[3]%d\n", tool->fork_ret[3]);
	printf("fork ret[4]%d\n", tool->fork_ret[4]);
	printf("forkret %p\n", tool->fork_ret);

	if (wait_all_children(data, tool->fork_ret, i) != 0)
	{
		close(tool->fd_stdin);
		free(tool->fork_ret);
		global_free(data, WAITPID_ERR);
	}
	// recuperer err de l'enfant

	dup2(tool->fd_stdin, 0);
	close(tool->fd_stdin);
}

void	executer(t_data *data)
{
	execute_cmds(data, data->cmds);
}

