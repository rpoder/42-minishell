/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
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
	char	*trimed_token;

	i = 0;
	while (dst[i])
	{
		trimed_token = token_trim(dst[i]);
		if (!trimed_token)
		{
			free(tool);
			global_free(data);
		}
		free(dst[i]);
		dst[i] = trimed_token;
		i++;
	}
}

char	*get_token_til_redir_operator(t_data *data, char *src, t_split_tool *tool)
{
	data->tokens[tool->nb_of_tokens] = get_token(data, src, tool);
	set_tool_for_next_token(tool, tool->i);
	return (data->tokens[tool->nb_of_tokens]);
}

static void	fill_dst(t_data *data, char *src, char **dst, t_split_tool *tool)
{
	tool->i = skip_space(src, 0);
	while (src[tool->i])
	{
		if (is_token_separator(src[tool->i]))
		{
			dst[tool->nb_of_tokens] = get_and_skip_token(data, src, tool);
			set_tool_for_next_token(tool, tool->i);
		}
		else if (src[tool->i] == '\'' || src[tool->i] == '\"')
		{
			tool->i = skip_quotes_token(src, tool->i);
			if (is_redirection_operator(src[tool->i]))
				dst[tool->nb_of_tokens] = get_token_til_redir_operator(data, src, tool);
			dst[tool->nb_of_tokens] = get_token_if_end_of_src(data, src, tool);
		}
		else
		{
			tool->i++;
			if (is_redirection_operator(src[tool->i]))
				dst[tool->nb_of_tokens] = get_token_til_redir_operator(data, src, tool);
			dst[tool->nb_of_tokens] = get_token_if_end_of_src(data, src, tool);
		}
	}
}

static int	count_words(char *src, int count)
{
	int	i;

	i = skip_space(src, 0);
	while (src[i])
	{
		if (is_token_separator(src[i]))
		{
			i = skip_separator(src, i);
			count++;
		}
		else if (src[i] == '\'' || src[i] == '\"')
		{
			i = skip_quotes_token(src, i);
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

void	split_tokens(t_data *data)
{
	int				count;
	t_split_tool	*split_tool;

	split_tool = init_split_tool();
	if (!split_tool)
		global_free(data);
	count = count_words(data->expanded_line, 0);
	data->tokens = malloc(sizeof(char *) * (count + 1));
	if (!data->tokens)
	{
		free(split_tool);
		global_free(data);
	}
	data->tokens = ft_set_ptr(data->tokens, count);
	fill_dst(data, data->expanded_line, data->tokens, split_tool);
	trim_dst(data, data->tokens, split_tool);
	free(split_tool);
}
