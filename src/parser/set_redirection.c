/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:51:22 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/16 16:52:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = NO_ERR;
	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{
		if (words[i][0] == '<' && !words[i][1] && words[i + 1])
			ret = set_fd_in(cmd, unmute_word(words[i + 1]));
		else if (words[i][0] == '<' && words[i][1] == '<'
			&& !words[i][2] && words[i + 1])
			ret = set_fd_heredoc(cmd, unmute_word(words[i + 1]));
		else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
			ret = set_fd_out(cmd, unmute_word(words[i + 1]), O_TRUNC);
		else if (words[i][0] == '>' && words[i][1] == '>' &&
			!words[i][2] && words[i + 1])
			ret = set_fd_out(cmd, unmute_word(words[i + 1]), O_APPEND);
		else
			return (PARSING_ERR);
		if (ret != NO_ERR)
			return (ret);
	}
	else
		return (PARSING_ERR);
	return (NO_ERR);
}

int	check_and_set_redirection(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = NO_ERR;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = set_fd(words, i, cmd);
			if (ret != NO_ERR)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (ret);
}
