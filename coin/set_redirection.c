/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:51:22 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/21 15:50:53 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(char **words, int i, t_cmd_node *cmd, t_p_tool *tool)
{
	char	*unmute_file;

	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{
		unmute_file = unmute_word(words[i + 1]);
		if (!unmute_file)
			return (MALLOC_ERR);
		if (words[i][0] == '<' && !words[i][1] && words[i + 1])
			tool->ret = set_fd_in(cmd, unmute_file);
		else if (words[i][0] == '<' && words[i][1] == '<'
			&& !words[i][2] && words[i + 1])
			tool->ret = set_fd_heredoc(cmd, unmute_file);
		else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
			tool->ret = set_fd_out(cmd, unmute_file, O_TRUNC);
		else if (words[i][0] == '>' && words[i][1] == '>' &&
			!words[i][2] && words[i + 1])
			tool->ret = set_fd_out(cmd, unmute_file, O_APPEND);
		else
			return (free(unmute_file), PARSING_ERR);
		free(unmute_file);
	}
	else
		tool->ret = PARSING_ERR;
	return (tool->ret);
}

// int	set_redirection(char **words, int i, t_cmd_node *cmd, t_p_tool *tool)
// {
// 	while (words[i] && words[i][0] != '|')
// 	{
// 		if (words[i][0] == '<' || words[i][0] == '>')
// 		{
// 			tool->ret = set_fd(words, i, cmd, tool);
// 			if (tool->ret != NO_ERR)
// 				return (tool->ret);
// 			i += 2;
// 		}
// 		else
// 			i++;
// 	}
// 	return (tool->ret);
// }
