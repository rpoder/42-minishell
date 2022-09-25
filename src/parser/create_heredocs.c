/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:57:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 23:16:48 by mpourrey         ###   ########.fr       */
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

static int	handle_heredoc_interruption(t_heredoc_tool *tool)
{
	if (dup2(tool->tmp_stdin, 0) == -1)
	{
		close(tool->tmp_stdin);
		return (dup_err);
	}
	if (close(tool->tmp_stdin) != 0)
		return (close_err);
	tool->ret = ctrl_c;
	return (tool->ret);
}

static int	get_and_write_lines(int fd, t_heredoc_tool *tool)
{
	tool->tmp_stdin = dup(0);
	if (tool->tmp_stdin == -1)
		return (dup_err);
	custom_heredoc_all_sigs();
	while (ft_strcmp(tool->carriaged_heredoc_line, tool->lim) != 0)
	{
		if (tool->carriaged_heredoc_line)
			free(tool->carriaged_heredoc_line);
		tool->heredoc_line = readline("heredoc> ");
		if (!tool->heredoc_line)
			return (handle_heredoc_interruption(tool));
		tool->carriaged_heredoc_line = ft_strjoin(tool->heredoc_line, "\n");
		free(tool->heredoc_line);
		if (!tool->carriaged_heredoc_line)
		{
			close(tool->tmp_stdin);
			return (malloc_err);
		}
		ft_putstr_fd(tool->carriaged_heredoc_line, fd);
	}
	free (tool->carriaged_heredoc_line);
	if (close(tool->tmp_stdin) != 0)
		return (close_err);
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
