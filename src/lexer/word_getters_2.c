/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_getters_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:42:54 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 14:57:21 by mpourrey         ###   ########.fr       */
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
		global_free(data, malloc_err);
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
		global_free(data, malloc_err);
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
	int		i;

	i = tool->i;
	j = 0;
	len = redirection_word_len(src, i);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		free(tool);
		global_free(data, malloc_err);
		return (word);
	}
	while (j < len)
	{
		word[j] = src[i];
		j++;
		i++;
	}
	word[j] = '\0';
	return (word);
}
