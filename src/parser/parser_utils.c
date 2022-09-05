/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:44:55 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/05 16:50:43 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_out(t_cmd_node *cmd, char *outfile, int flag)
{
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (is_redirection_operator(outfile[0]))
		return (-1);
	if (flag == O_APPEND)
		cmd->fd_out = open(outfile, O_RDWR | O_APPEND);
	else if (flag == O_TRUNC)
		cmd->fd_out = open(outfile, O_RDWR | O_TRUNC);
	if (cmd->fd_out < 0)
		cmd->fd_out = open(outfile, O_RDWR | O_CREAT, 0644);
	if (cmd->fd_out < 0)
		ft_printf_fd("minilsshell: %s: Permission denied\n", 2, outfile);
	return (0);
}

int	set_fd_in(t_cmd_node *cmd, char *infile)
{
	if (cmd->fd_in >= 0)
		close(cmd->fd_out);
	if (is_redirection_operator(infile[0]))
		return (-1);
	cmd->fd_in = open(infile, O_RDONLY);
	if (cmd->fd_in < 0)
		ft_printf_fd("minilsshell: %s: Permission denied\n", 2, infile);
	return (0);
}

int	open_heredoc(void)
{
	char	*heredoc;
	int		fd_heredoc;
	int		i;
	char	*nb;

	i = 0;
	fd_heredoc = -2;
	while (fd_heredoc < 0 && i < INT_MAX)
	{
		nb = ft_itoa(i);
		if (!nb)
			return (-2);
		heredoc = ft_strjoin("heredoc_", nb);
		if (!heredoc)
		{
			free(nb);
			return (-2);
		}
		fd_heredoc = open(heredoc, O_RDWR | O_TRUNC | O_CREAT, 0644);
		free(nb);
		free(heredoc);
		i++;
	}
	if (fd_heredoc < 0)
		ft_printf_fd("minilsshell: heredoc: Permission denied\n", 2);
	return (fd_heredoc);
}

int	set_fd_heredoc(t_cmd_node *cmd, char *lim)
{
	char	*limiter;
	char	*str;

	cmd->fd_in = open_heredoc();
	if (cmd->fd_in == -2)
		return (-1);
	printf("fd_heredoc = %d\n", cmd->fd_in);
	/* limiter = ft_strjoin(argv[2], "\n");
	write(0, "> ", 2);
	str = get_next_line(0);
	while (str != NULL && ft_strcmp(str, limiter) != 0)
	{
		write(fd_heredoc, str, ft_strlen(str));
		free(str);
		write(0, "> ", 2);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
	free(limiter);
	close(fd_heredoc);
	fd_heredoc = open(argv[1], O_RDWR); */
//	return (fd_heredoc);
	return (0);
}


