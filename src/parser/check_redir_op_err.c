/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_op_err.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:52:52 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 14:58:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_op_err(char **words, int i)
{
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
			{
				if ((!words[i][1]) || (words[i][0] == '<' && words[i][1] == '<'
					&& !words[i][2])
					|| (words[i][0] == '>' && words[i][1] == '>'
					&& !words[i][2]))
					i += 2;
				else
					return (parsing_err);
			}
			else
				return (parsing_err);
		}
		else
			i++;
	}
	return (no_err);
}
