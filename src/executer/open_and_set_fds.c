/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_set_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:42:26 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 03:06:18 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_set_fd(char **words, int i, t_cmd_node *cmd)
{
	char	*unmute_file;
	int		ret;

	ret = NO_ERR;
	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{
		unmute_file = unmute_word(words[i + 1]);
		if (!unmute_file)
			return (MALLOC_ERR);
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
		else
			return (free(unmute_file), PARSING_ERR); ///////////////////////
		free(unmute_file);
	}
	else
		ret = PARSING_ERR; /////////////////////////////
	return (ret);
}

int	open_and_set_fds(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = NO_ERR;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = open_and_set_fd(words, i, cmd);
			if (ret != NO_ERR)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (ret);
}
