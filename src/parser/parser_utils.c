/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:44:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/03 17:11:52 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd_out(t_data *data, t_cmd_node *cmd, char *outfile, int flag)
{
	if (flag == O_APPEND)
		cmd->fd_out = open(outfile, O_RDWR | O_APPEND);
	else if (flag == O_TRUNC)
		cmd->fd_out = open(outfile, O_RDWR | O_TRUNC);
	if (cmd->fd_out < 0)
		cmd->fd_out = open(outfile, O_RDWR | O_CREAT, 0644);
	// securiser
}

void	set_fd_in(t_data *data, t_cmd_node *cmd, char *infile)
{
	cmd->fd_in = open(infile, O_RDONLY);
	// securiser
}

void	set_fd_heredoc(t_data *data, t_cmd_node *cmd, char *lim)
{
	//toz
}


