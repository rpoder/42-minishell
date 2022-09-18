/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/18 16:41:44 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	fill_with_muted_key(t_data *data, t_expand_tool *tool)
{
	int		i;
	int		j;
	int		k;
	char	*expand_key;

	i = tool->len;
	j = tool->i;
	k = 0;
	expand_key = get_expand_key(data->prompt_line, i + 1);
	if (!expand_key)
	{
		free(tool->quotes);
		free(tool);
		global_free(data, MALLOC_ERR);
	}
	(data->expanded_line)[j] = '*' * -1;
	j++;
 	while (expand_key[k])
	{
		(data->expanded_line)[j] = expand_key[k] * -1;
		j++;
		k++;
	}
	free(expand_key);
} */

static void	fill_with_expand_value(t_data *data, t_expand_tool *tool)
{
	char	*expand_value;
	char	*expand_key;
	int		i;
	int		j;
	int		k;

	i = tool->len;
	j = tool->i;
	k = 0;
	expand_key = get_expand_key(data->prompt_line, i + 1);
	if (!expand_key)
	{
		free(tool->quotes);
		free(tool);
		global_free(data, MALLOC_ERR);
	}
	expand_value = get_expand_value(data, expand_key);
	while (expand_value[k])
	{
		data->expanded_line[j] = expand_value[k];
		j++;
		k++;
	}
	free (expand_key);
}

static void	fill_and_skip_expand(t_data *data, t_expand_tool *tool)
{
	int	exp_value_len;

	exp_value_len = expand_value_len(data, data->prompt_line, tool->len + 1);
	if (exp_value_len < 0)
	{
		free_expand_tool(tool);
		global_free(data, MALLOC_ERR);
	}
	else if (exp_value_len > 0)
	{
		fill_with_expand_value(data, tool);
		tool->i += exp_value_len;
	}
	else if (exp_value_len == 0)
	{
		(data->expanded_line)[tool->i] = '*' * -1;
		save_ambiguous_redirect(data, data->prompt_line, tool->len, tool); /////////////save_ambiguous_redirection
		tool->i += 1;
	}
	tool->len += expand_key_len(data->prompt_line, tool->len + 1);
}

static void	fill_expanded_line(t_data *data, t_expand_tool *tool)
{
	clear_expand_tool(tool);
	while (data->prompt_line[tool->len])
	{
		set_quotes(data->prompt_line[tool->len], tool->quotes);
		if (data->prompt_line[tool->len] == '$' && is_expand_to_interpret
			(data->prompt_line, tool->len, tool->quotes))
				fill_and_skip_expand(data, tool);
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
		data->expanded_line = ft_alloc_and_fill(data->prompt_line);
		if (!data->expanded_line)
			global_free(data, MALLOC_ERR);
		return ;
	}
	expand_tool = init_expand_tool();
	if (!expand_tool)
		global_free(data, MALLOC_ERR);
	dst_len = expanded_line_len(data, data->prompt_line, expand_tool);
	data->expanded_line = malloc(sizeof(char) * (dst_len + 1));
	if (!data->expanded_line)
	{
		free_expand_tool(expand_tool);
		global_free(data, MALLOC_ERR);
	}
	fill_expanded_line(data, expand_tool);
	free_expand_tool(expand_tool);
}
