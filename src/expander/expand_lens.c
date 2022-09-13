/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:01:07 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/13 22:22:50 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_key_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !is_expand_separator(str[i])
		&& !is_expand_suffix(str[i], len))
	{
		len++;
		i++;
	}
	return (len);
}

int	expand_value_len(t_data *data, char *str, int start)
{
	int		expand_value_len;
	int		expand_key_len;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(str, start);
	if (!expand_key)
	{
		return (-1);
	}
	expand_value = get_expand_value(data, expand_key);
	free(expand_key);
	if (!expand_value)
		return (0);
	expand_value_len = ft_strlen(expand_value);
	return (expand_value_len);
}

int	expanded_line_len(t_data *data, char *str, t_expand_tool *tool)
{
	int	tmp;

	while (str[tool->i])
	{
		set_quotes(str[tool->i], tool->quotes);
		if (str[tool->i] == '$' && is_expand_to_interpret(str, tool->i,
				tool->quotes))
		{
			tmp = expand_value_len(data, str, tool->i + 1);
			if (tmp == 0)
				tmp = (expand_key_len(str, tool->i + 1) + 1);
			if (tmp < 0)
			{
				free_expand_tool(tool);
				global_free(data, MALLOC_ERR);
			}
			tool->len = tool->len + tmp;
			tool->i = tool->i + expand_key_len(str, tool->i + 1);
		}
		else
			tool->len++;
		tool->i++;
	}
	return (tool->len);
}
