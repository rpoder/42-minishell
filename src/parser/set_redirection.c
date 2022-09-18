/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:51:22 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/18 18:21:45 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(char **words, int i, t_cmd_node *cmd, char *amb_redir)
{
	int		ret;
	char	*unmute_file;

	ret = NO_ERR;
	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{
		unmute_file = unmute_word(words[i + 1]);
		if (!unmute_file)
			return (MALLOC_ERR);
		if (words[i][0] == '<' && !words[i][1] && words[i + 1])
			ret = set_fd_in(cmd, unmute_file, amb_redir);
		else if (words[i][0] == '<' && words[i][1] == '<'
			&& !words[i][2] && words[i + 1])
			ret = set_fd_heredoc(cmd, unmute_file);
		else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
			ret = set_fd_out(cmd, unmute_file, O_TRUNC, amb_redir);
		else if (words[i][0] == '>' && words[i][1] == '>' &&
			!words[i][2] && words[i + 1])
			ret = set_fd_out(cmd, unmute_file, O_APPEND, amb_redir);
		else
		{
			free(unmute_file);
			return (PARSING_ERR);
		}
		free(unmute_file);
		if (ret != NO_ERR)
			return (ret);
	}
	else
		return (PARSING_ERR);
	return (NO_ERR);
}

int	check_and_set_redirection(char **words, int i, t_cmd_node *cmd, char *amb_redir)
{
	int	ret;

	ret = NO_ERR;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = set_fd(words, i, cmd, amb_redir);
			if (ret != NO_ERR)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (ret);
}
