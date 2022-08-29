/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/29 14:21:33 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expanded_line_len(t_data *data, char *str, t_expand_tool *tool)
{
	int	tmp;

	while (str[tool->i])
	{
		tool->quotes = set_quotes(str[tool->i], tool->quotes);
		if (str[tool->i] == '$' && is_expand_to_interpret(str, tool->i,
				tool->quotes))
		{
			tmp = expand_value_len(data, str, tool->i + 1);
			if (tmp > 0)
			{
				tool->i = tool->i + expand_key_len(str, tool->i + 1);
				tool->len = tool->len + tmp;
			}
			else
				tool->len++;
		}
		else
			tool->len++;
		tool->i++;
	}
	return (tool->len);
}

static void	fill_with_expand_value(t_data *data, int i, int j)
{
	char	*expand_value;
	char	*expand_key;
	int		k;

	k = 0;
	expand_key = get_expand_key(data->prompt_line, i + 1);
	if (!expand_key)
		global_free(data);
	expand_value = get_expand_value(data, expand_key);
	free (expand_key);
	if (expand_value)
	{
		while (expand_value[k])
		{
			data->expanded_line[j] = expand_value[k];
			j++;
			k++;
		}
	}
}

static void	fill_expanded_line(t_data *data, t_expand_tool *tool)
{
	int	exp_value_len;

	tool = clear_expand_tool(tool);
	while (data->prompt_line[tool->len])
	{
		tool->quotes = set_quotes(data->prompt_line[tool->len], tool->quotes);
		if (data->prompt_line[tool->len] == '$' && is_expand_to_interpret
			(data->prompt_line, tool->len, tool->quotes))
		{	
			fill_with_expand_value(data, tool->len, tool->i);
			exp_value_len = expand_value_len(data, data->prompt_line,
					tool->len + 1);
			tool->i = tool->i + exp_value_len;
			if (exp_value_len < 0)
				global_free(data);
			tool->len += expand_key_len(data->prompt_line, tool->len + 1);
		}
		else
		{
			data->expanded_line[tool->i] = data->prompt_line[tool->len];
			tool->i++;
		}
		tool->len++;
	}
	data->expanded_line[tool->i] = '\0';
}

void	expander(t_data *data)
{
	int				dst_len;
	t_expand_tool	*expand_tool;

	if (!has_expand(data->prompt_line))
	{
		data->expanded_line = alloc_and_fill(data->prompt_line);
		return ;
	}
	expand_tool = init_expand_tool();
	if (!expand_tool)
		global_free(data);
	dst_len = expanded_line_len(data, data->prompt_line, expand_tool);
	data->expanded_line = malloc(sizeof(char) * (dst_len + 1));
	if (!data->expanded_line)
		global_free(data);
	fill_expanded_line(data, expand_tool);
	free(expand_tool->quotes);
	free(expand_tool);
}
