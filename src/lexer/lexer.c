/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/30 22:11:03 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_dst(t_data *data, char **dst, t_split_tool *tool)
{
	int		i;
	char	*trimed_word;

	i = 0;
	while (dst[i])
	{
		trimed_word = word_trim(dst[i]);
		if (!trimed_word)
		{
			free(tool);
			global_free(data, MALLOC_ERR);
		}
		free(dst[i]);
		dst[i] = trimed_word;
		i++;
	}
}

static void	fill_dst(t_data *data, char *src, char **dst, t_split_tool *tool)
{
	tool->i = skip_space(src, 0);
	while (src[tool->i])
	{
		if (is_word_separator(src[tool->i]))
		{
			dst[tool->nb_of_words] = get_and_skip_word(data, src, tool);
			set_tool_for_next_word(tool, tool->i);
		}
		else if (src[tool->i] == '\'' || src[tool->i] == '\"')
		{
			tool->i = skip_quotes_word(src, tool->i);
			if (is_redirection_operator(src[tool->i]))
				dst[tool->nb_of_words] = get_word_til_redir_op(data, src, tool);
			dst[tool->nb_of_words] = get_word_if_end_of_src(data, src, tool);
		}
		else
		{
			tool->i++;
			if (is_redirection_operator(src[tool->i]))
				dst[tool->nb_of_words] = get_word_til_redir_op(data, src, tool);
			dst[tool->nb_of_words] = get_word_if_end_of_src(data, src, tool);
		}
	}
}

static int	count_words(char *src, int count)
{
	int	i;

	i = skip_space(src, 0);
	while (src[i])
	{
		if (is_word_separator(src[i]))
		{
			i = skip_separator(src, i);
			count++;
		}
		else if (src[i] == '\'' || src[i] == '\"')
		{
			i = skip_quotes_word(src, i);
			if (src[i] == '\0' || is_redirection_operator(src[i]))
				count++;
		}
		else
		{
			i++;
			if (src[i] == '\0' || is_redirection_operator(src[i]))
				count++;
		}
	}
	return (count);
}

void	lexer(t_data *data)
{
	int				count;
	t_split_tool	*split_tool;

	split_tool = init_split_tool();
	if (!split_tool)
		global_free(data, MALLOC_ERR);
	count = count_words(data->expanded_line, 0);
	data->words = malloc(sizeof(char *) * (count + 1));
	if (!data->words)
	{
		free(split_tool);
		global_free(data, MALLOC_ERR);
	}
	data->words = ft_set_ptr(data->words, count);
	fill_dst(data, data->expanded_line, data->words, split_tool);
	trim_dst(data, data->words, split_tool);
	free(split_tool);
}
