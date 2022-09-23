/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_tool_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:02:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 04:41:18 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_tool(t_exec_tool **tool)
{
	if ((*tool)->pipe_fd)
	{
		if ((*tool)->pipe_fd[0] >= 0)
			close ((*tool)->pipe_fd[0]);
		if ((*tool)->pipe_fd[1] >= 0)
			close ((*tool)->pipe_fd[1]);
		free((*tool)->pipe_fd);
	}
	if ((*tool)->fork_ret)
		free((*tool)->fork_ret);
	if ((*tool)->fd_stdin >= 0)
		close ((*tool)->fd_stdin);
	if ((*tool)->fd_stdout >= 0)
		close ((*tool)->fd_stdout);
	free(*tool);
	*tool = NULL;
}

static int	*init_pipe_fd(void)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		return (NULL);
	pipe_fd[0] = FD_UNDEFINED;
	pipe_fd[1] = FD_UNDEFINED;
	return (pipe_fd);
}

static int	*init_fork_ret(t_list *cmd)
{
	int		len;
	int	*fork_ret;

	len = ft_lstlen(cmd);
	fork_ret = malloc(sizeof(int) * len);
	if (!fork_ret)
		return (NULL);
	while (len > 0)
	{
		fork_ret[len - 1] = FD_UNDEFINED;
		len--;
	}
	return (fork_ret);
}

t_exec_tool	*init_exec_tool(t_list *cmd)
{
	t_exec_tool	*tool;

	tool = malloc(sizeof(t_exec_tool));
	if (!tool)
		return (NULL);
	tool->i = 0;
	tool->ret = NO_ERR;
	tool->fd_stdin = dup(0);
	if (tool->fd_stdin < 0)
	{
		free(tool);
		return (NULL);
	}
	tool->fd_stdout = dup(1);
	if (tool->fd_stdout < 0)
	{
		close (tool->fd_stdin);
		free(tool);
		return (NULL);
	}
	tool->fork_ret = init_fork_ret(cmd);
	if (!tool->fork_ret)
	{
		close (tool->fd_stdin);
		close (tool->fd_stdout);
		free(tool);
		return (NULL);
	}
	tool->pipe_fd = init_pipe_fd();
	if (!tool->pipe_fd)
	{
		close (tool->fd_stdin);
		close (tool->fd_stdout);
		free(tool->fork_ret);
		free(tool);
		return (NULL);
	}
	return (tool);
}
