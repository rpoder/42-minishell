/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:31:00 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/07 13:42:47 by mpourrey         ###   ########.fr       */
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

static char	*get_heredoc_name(int i)
{
	char	*nb;
	char	*heredoc;

	nb = ft_itoa(i);
	if (!nb)
		return (NULL);
	if (access("tmp/", F_OK) == 0)
		heredoc = ft_strjoin("/tmp/heredoc_", nb);
	else
		heredoc = ft_strjoin("heredoc_", nb);
	if (!heredoc)
	{
		free(nb);
		return (NULL);
	}
	free(nb);
	return (heredoc);
}

static int	open_heredoc(char **heredoc_path)
{
	char	*heredoc;
	int		fd_heredoc;
	int		i;

	i = 0;
	fd_heredoc = -2;
	while (fd_heredoc < 0 && i < INT_MAX)
	{
		heredoc = get_heredoc_name(i);
		if (!heredoc)
			return (-2);
		fd_heredoc = open(heredoc, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd_heredoc < 0)
			free(heredoc);
		i++;
	}
	if (fd_heredoc < 0)
		ft_printf_fd("minilsshell: heredoc: Permission denied\n", 2);
	else
	{
		*heredoc_path = heredoc;
		free(heredoc);
	}
	return (fd_heredoc);
}

int	set_fd_heredoc(t_cmd_node *cmd, char *lim)
{
	char	*str;
	char	*heredoc_path;

	cmd->fd_in = open_heredoc(&heredoc_path);
	if (cmd->fd_in == -2)
		return (-1);
	lim = ft_strjoin(lim, "\n");
	if (!lim)
		return (-1);
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str != NULL && ft_strcmp(str, lim) != 0)
	{
		write(cmd->fd_in, str, ft_strlen(str));
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
	free(lim);
	close(cmd->fd_in);
	cmd->fd_in = open(heredoc_path, O_RDWR);
	return (0);
}
