/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_set_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:42:26 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 15:11:05 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_set_fd(char **words, int i, t_cmd_node *cmd)
{
	char	*unmute_file;
	int		ret;

	unmute_file = unmute_word(words[i + 1]);
	if (!unmute_file)
		return (malloc_err);
	if (words[i][0] == '<' && !words[i][1] && words[i + 1])
		ret = open_and_set_fd_in(cmd, unmute_file);
	else if (words[i][0] == '<' && words[i][1] == '<'
		&& !words[i][2] && words[i + 1])
		ret = open_and_set_fd_heredoc(cmd);
	else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
		ret = open_and_set_fd_out(cmd, unmute_file, O_TRUNC);
	else if (words[i][0] == '>' && words[i][1] == '>' &&
		!words[i][2] && words[i + 1])
		ret = open_and_set_fd_out(cmd, unmute_file, O_APPEND);
	free(unmute_file);
	return (ret);
}

int	open_and_set_fds(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = no_err;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = open_and_set_fd(words, i, cmd);
			if (ret != no_err)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (ret);
}
