/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:42:01 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/30 22:11:12 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_and_skip_word(t_data *data, char *src, t_split_tool *tool)
{
	char	*word;

	if (is_redirection_operator(src[tool->i]))
	{
		word = get_redir_op_word(data, src, tool);
		{
			printf("redir op word = %s\n", word);
		}
	}
	else if (is_space(src[tool->i]))
		word = get_word_til_space(data, src, tool);
	tool->i = skip_separator(src, tool->i);
	return (word);
}

char	*get_word_til_redir_op(t_data *data, char *src, t_split_tool *tool)
{
	data->words[tool->nb_of_words] = get_word(data, src, tool);
	set_tool_for_next_word(tool, tool->i);
	return (data->words[tool->nb_of_words]);
}

char	*get_word_if_end_of_src(t_data *data, char *src, t_split_tool *tool)
{
	char	*word;

	word = NULL;
	if (src[tool->i] == '\0')
		word = get_word(data, src, tool);
	return (word);
}
