/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:49:02 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 19:50:35 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_data *data, t_exec_tool *tool)
{
	if (pipe(tool->pipe_fd) != 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, pipe_err);
	}
}

void	handle_fork(t_data *data, t_exec_tool *tool)
{
	tool->fork_ret[tool->i] = fork();
	if (tool->fork_ret[tool->i] < 0)
	{
		free_exec_tool(&tool);
		close(tool->fd_stdin);
		global_free(data, fork_err);
	}
}

void	redirect_to_pipe(t_data *data, t_exec_tool *tool)
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
