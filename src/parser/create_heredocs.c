/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:57:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 20:30:48 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (malloc_err);
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
		return (open_err);
	}
	*heredoc_path = heredoc;
	return (fd_heredoc);
}

static int	get_and_write_lines(int fd, t_heredoc_tool *tool)
{
	char	*line;
	char	*n_line;

	line = NULL;
	n_line = NULL;
	while (ft_strcmp(n_line, tool->lim) != 0 && g_close_heredoc == false)
	{
		if (n_line)
			free(n_line);
		line = readline("heredoc> ");
		if (!line)
		{
			tool->ret = ctrl_c;
			return (tool->ret);
		}
		n_line = ft_strjoin(line, "\n");
		free(line);
		if (!n_line)
			return (malloc_err);
		write(fd, n_line, ft_strlen(n_line));
	}
	free (n_line);
	if (g_close_heredoc == true)
		return (ctrl_c);
	return (no_err);
}

static int	create_one_heredoc(t_cmd_node *cmd, char *lim)
{
	t_heredoc_tool	*tool;
	int				ret;

	tool = init_heredoc_tool(lim);
	if (!tool)
		return (malloc_err);
	cmd->fd_in = open_heredoc(&tool->heredoc_path);
	if (cmd->fd_in == malloc_err)
		return (free_heredoc_tool(tool), malloc_err);
	ret = add_path_to_heredoc_list(cmd, tool->heredoc_path);
	if (ret != no_err)
	{
		close(cmd->fd_in);
		return (free_heredoc_tool(tool), ret);
	}
	ret = get_and_write_lines(cmd->fd_in, tool);
	if (close(cmd->fd_in) != 0)
		return (free_heredoc_tool(tool), close_err);
	if (ret != no_err)
		return (free_heredoc_tool(tool), ret);
	free_heredoc_tool(tool);
	return (no_err);
}

int	create_heredocs(char **words, int i, t_cmd_node *cmd, t_p_tool *tool)
{
	char	*unmute_file;

	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' && words[i][1] == '<')
		{
			if (!words[i][2] && words[i + 1] &&
				!is_redirection_operator(words[i + 1][0]))
			{
				unmute_file = unmute_word(words[i + 1]);
				if (!unmute_file)
					return (malloc_err);
				tool->ret = create_one_heredoc(cmd, unmute_file);
				free(unmute_file);
				if (tool->ret != no_err)
					return (tool->ret);
				i += 2;
			}
			else
				return (parsing_err);
		}
		else
			i++;
	}
	return (tool->ret);
}
