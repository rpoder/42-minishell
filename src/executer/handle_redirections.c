/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:37:29 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/17 17:58:36 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_pipe_out(t_data *data, int *pipe_fd)
{
	if (dup2(pipe_fd[0], 0) < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		global_free(data, DUP_ERR);
	}
	if (close(pipe_fd[0]) != 0)
	{
		close(pipe_fd[1]);
		global_free(data, DUP_ERR);
	}
	if (close(pipe_fd[1]) != 0)
		global_free(data, DUP_ERR);
}

void	chevron_redirection(t_data *data, t_cmd_node *cmd, t_exec_tool *tool)
{
	if (cmd->fd_in >= -1)
	{
		if (dup2(cmd->fd_in, 0) < 0)
		{
			if (cmd->fd_in >= 0)
				close(cmd->fd_in);
			if (cmd->fd_out >= 0)
				close(cmd->fd_out);
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
	}
	if (cmd->fd_out >= -1)
	{
		if (dup2(cmd->fd_out, 1) < 0)
		{
			if (cmd->fd_in >= 0)
				close(cmd->fd_in);
			if (cmd->fd_out >= 0)
				close(cmd->fd_out);
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
	}
}
