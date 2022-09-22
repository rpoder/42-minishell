/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:57:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 13:39:04 by rpoder           ###   ########.fr       */
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
	*heredoc_path = heredoc;
	return (fd_heredoc);
}

static int	get_and_write_lines(int fd, t_heredoc_tool *tool, t_p_tool *p_tool)
{
	int	fork_ret;

	cancel_parent_signals();
	fork_ret = fork();
	if (fork_ret < 0)
		return (FORK_ERR);
	if (fork_ret == 0)
	{
		create_child_signals();
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
				global_free(g_data, MALLOC_ERR);
		}
		// free(line);
		// free_heredoc_tool(tool);
		// free(p_tool);
		// close(fd);
		global_free(g_data, NO_ERR);
		// exit(0);
	}
	waitpid(fork_ret, NULL, 0);
	return (NO_ERR);
}

int	create_one_heredoc(t_cmd_node *cmd, char *lim, t_p_tool *p_tool)
{
	t_heredoc_tool	*tool;
	int				ret;
	int				fork_ret;

		// create_child_signals();
		tool = init_heredoc_tool(lim);
		if (!tool)
			return (MALLOC_ERR);
		cmd->fd_in = open_heredoc(&tool->heredoc_path);
		if (cmd->fd_in == MALLOC_ERR)
			return (free_heredoc_tool(tool), MALLOC_ERR);
		ret = add_path_to_heredoc_list(cmd, tool->heredoc_path);
		if (ret != NO_ERR)
		{
			close(cmd->fd_in);
			return (free_heredoc_tool(tool), ret);
		}

		ret = get_and_write_lines(cmd->fd_in, tool, p_tool);
		close(cmd->fd_in);
		if (ret != NO_ERR)
			return (free_heredoc_tool(tool), ret);
		free_heredoc_tool(tool);
		return (NO_ERR);
}


int	create_heredocs(char **words, int i, t_cmd_node *cmd, t_p_tool *tool)
{
	char	*unmute_file;

	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' && words[i][1] == '<')
		{
			if (!words[i][2] && words[i + 1] && !is_redirection_operator(words[i + 1][0]))
			{
				unmute_file = unmute_word(words[i + 1]);
				if (!unmute_file)
					return (MALLOC_ERR);
				tool->ret = create_one_heredoc(cmd, unmute_file, tool);
				free(unmute_file);
				if (tool->ret != NO_ERR)
					return (tool->ret);
				i += 2;
			}
			else
				return (PARSING_ERR);
		}
		else
			i++;
	}
	return (tool->ret);
}
