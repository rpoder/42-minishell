/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:52:02 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 20:52:14 by rpoder           ###   ########.fr       */
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
