/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_getters_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:42:54 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/01 11:21:21 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(t_data *data, char *src, t_split_tool *tool)
{
	char	*word;
	int		len;
	int		j;

	j = 0;
	len = tool->i - tool->word_start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		free(tool);
		global_free(data, MALLOC_ERR);
		return (word);
	}
	while (src[tool->word_start] != '\0'
		&& !is_redirection_operator(src[tool->word_start]))
	{
		word[j] = src[tool->word_start];
		j++;
		tool->word_start++;
	}
	word[j] = '\0';
	return (word);
}

char	*get_word_til_space(t_data *data, char *src, t_split_tool *tool)
{
	char	*word;
	int		len;
	int		j;

	j = 0;
	len = tool->i - tool->word_start;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
	{
		free(tool);
		global_free(data, MALLOC_ERR);
		return (word);
	}
	while (tool->word_start < tool->i)
	{
		word[j] = src[tool->word_start];
		j++;
		tool->word_start++;
	}
	word[j] = '\0';
	return (word);
}

char	*get_redir_op_word(t_data *data, char *src, t_split_tool *tool)
{
	char	*word;
	int		len;
	int		j;

	j = 0;
	len = redirection_word_len(src, tool->i);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		free(tool);
		global_free(data, MALLOC_ERR);
		return (word);
	}
	while (j < len)
	{
		word[j] = src[tool->i];
		j++;
	}
	word[j] = '\0';
	return (word);
}
