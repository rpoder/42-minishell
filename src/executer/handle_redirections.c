/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:37:29 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/15 11:48:06 by margot           ###   ########.fr       */
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

void	chevron_redirection(t_data *data, t_cmd_node *cmd)
{
	if (cmd->fd_in >= -1)
	{
		if (dup2(cmd->fd_in, 0) < 0)
		{
			close(cmd->fd_in);
			close(cmd->fd_out);
			global_free(data, DUP_ERR);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= -1)
	{
		if (dup2(cmd->fd_out, 1) < 0)
		{
			close(cmd->fd_in);
			close(cmd->fd_out);
			global_free(data, DUP_ERR);
		}
		close(cmd->fd_out);
	}

}
