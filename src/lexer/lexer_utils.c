/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:21:42 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 16:10:52 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_node(char **words, int len)
{
	while (words[len] && words[len][0] != '|')
		len++;
	if (words[len])
		len++;
	return (len);
}

t_split_tool	*init_split_tool(void)
{
	t_split_tool	*split_tool;

	split_tool = malloc(sizeof(t_split_tool));
	if (!split_tool)
		return (NULL);
	split_tool->i = 0;
	split_tool->nb_of_words = 0;
	split_tool->word_start = 0;
	return (split_tool);
}

void	set_tool_for_next_word(t_split_tool *split_tool, int i)
{
	split_tool->nb_of_words++;
	split_tool->word_start = i;
}

int	redirection_word_len(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
		{
			len++;
			i++;
		}
	}
	else if (str[i] == '|')
	{
		while (str[i] && str[i] == '|')
		{
			len++;
			i++;
		}
	}
	return (len);
}
