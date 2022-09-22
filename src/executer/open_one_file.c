/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_one_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:42:34 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 02:15:53 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_and_set_fd_out(t_cmd_node *cmd, char *outfile, int flag)
{
	if (!outfile[0])
	{
		cmd->fd_out = -1;
		ft_printf_fd("minilsshell: ambiguous redirect\n", 2);
		return (OPEN_ERR);
	}
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (is_redirection_operator(outfile[0]))
		return (PARSING_ERR);
	if (flag == O_APPEND)
		cmd->fd_out = open(outfile, O_RDWR | O_APPEND);
	else if (flag == O_TRUNC)
		cmd->fd_out = open(outfile, O_RDWR | O_TRUNC);
	if (cmd->fd_out < 0)
		cmd->fd_out = open(outfile, O_RDWR | O_CREAT, 0644);
	if (cmd->fd_out < 0)
	{
		ft_printf_fd("minilsshell: ", 2);
		perror(outfile);
		return (OPEN_ERR);
	}
	return (NO_ERR);
}

int	open_and_set_fd_in(t_cmd_node *cmd, char *infile)
{
	if (!infile[0])
	{
		cmd->fd_in = -1;
		ft_printf_fd("minilsshell: ambiguous redirect\n", 2);
		return (OPEN_ERR);
	}
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (is_redirection_operator(infile[0]))
		return (PARSING_ERR);
	cmd->fd_in = open(infile, O_RDONLY);
	if (cmd->fd_in < 0)
	{
		ft_printf_fd("minilsshell: ", 2);
		perror(infile);
		return (OPEN_ERR);
	}
	return (NO_ERR);
}

int	open_and_set_fd_heredoc(t_cmd_node *cmd)
{
	t_list	*heredoc_node;
	
	heredoc_node = ft_lstlast(cmd->heredocs);
	cmd->fd_in = open(((char *)heredoc_node->content), O_RDONLY);
	if (cmd->fd_in < 0)
	{
		ft_printf_fd("minilsshell: ", 2);
		perror((char *)heredoc_node->content);
		return (OPEN_ERR);
	}
	return (NO_ERR);
}
