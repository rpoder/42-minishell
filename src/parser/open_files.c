/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:31:00 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/17 12:37:03 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_out(t_cmd_node *cmd, char *outfile, int flag)
{
	if (outfile[0] < 0)
	{
		print_ambiguous_redirection(outfile);
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

int	set_fd_in(t_cmd_node *cmd, char *infile)
{
	if (infile[0] < 0)
	{
		print_ambiguous_redirection(infile);
		return (OPEN_ERR);
	}
	if (cmd->fd_in >= 0)
		close(cmd->fd_out);
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

static int	open_heredoc(char **heredoc_path)
{
	char	*heredoc;
	int		fd_heredoc;
	int		i;

	i = 0;
	fd_heredoc = FD_UNDEFINED;
	while (fd_heredoc < 0 && i < INT_MAX)
	{
		heredoc = get_heredoc_name(i);
		if (!heredoc)
			return (MALLOC_ERR);
		fd_heredoc = open(heredoc, O_RDWR | O_TRUNC | O_CREAT | O_EXCL, 0644);
		if (fd_heredoc < 0)
			free(heredoc);
		i++;
	}
	if (fd_heredoc < 0)
	{
		free(heredoc);
		ft_printf_fd("minilsshell: heredoc: ", 2);
		perror(heredoc);
		return (OPEN_ERR);
	}
	else
		*heredoc_path = heredoc;
	return (fd_heredoc);
}

static int	get_and_write_lines(int fd, t_heredoc_tool *tool)
{
	int	ret;

	write(1, "> ", 2);
	tool->str = gnl_minishell(0, tool->ret);
	if (*(tool->ret) != NO_ERR)
		return (*(tool->ret));
	while (tool->str != NULL && ft_strcmp(tool->str, tool->lim) != 0)
	{
		write(fd, tool->str, ft_strlen(tool->str));
		free(tool->str);
		write(1, "> ", 2);
		tool->str = gnl_minishell(0, tool->ret);
		if (*(tool->ret) != NO_ERR)
			return (*(tool->ret));
	}
	return (NO_ERR);
}

int	set_fd_heredoc(t_cmd_node *cmd, char *lim)
{
	t_heredoc_tool	*tool;
	int				ret;
	t_list			*heredoc_node;

	tool = init_heredoc_tool(lim);
	if (!tool)
		return (MALLOC_ERR);
	cmd->fd_in = open_heredoc(&tool->heredoc_path);
	if (tool->heredoc_path)
	{
		heredoc_node = ft_lstnew(ft_alloc_and_fill(tool->heredoc_path));
		ft_lstadd_back(&cmd->heredocs, heredoc_node);
	}
	if (cmd->fd_in == MALLOC_ERR)
	{
		free(tool);
		return (MALLOC_ERR);
	}
	ret = get_and_write_lines(cmd->fd_in, tool);
	close(cmd->fd_in);
	if (ret != NO_ERR)
	{
		free_heredoc_tool(tool);
		return (ret);
	}
	cmd->fd_in = open(tool->heredoc_path, O_RDWR);
	free_heredoc_tool(tool);
	return (NO_ERR);
}
