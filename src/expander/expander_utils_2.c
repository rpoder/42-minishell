/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/31 16:42:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_expand_tool(t_expand_tool *expand_tool)
{
	expand_tool->i = 0;
	expand_tool->len = 0;
	clear_quotes(expand_tool->quotes);
}

t_expand_tool	*init_expand_tool(void)
{
	t_expand_tool	*expand_tool;

	expand_tool = malloc(sizeof(t_expand_tool));
	if (!expand_tool)
		return (NULL);
	expand_tool->i = 0;
	expand_tool->len = 0;
	expand_tool->quotes = malloc(sizeof(t_quotes));
	if (!expand_tool->quotes)
	{
		free(expand_tool);
		return (NULL);
	}
	clear_expand_tool(expand_tool);
	return (expand_tool);
}

int	expand_key_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !is_separator(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	expand_value_len(t_data *data, char *str, int i)
{
	int		expand_value_len;
	int		expand_key_len;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(str, i);
	if (!expand_key)
		return (-1);
	expand_value = get_expand_value(data, expand_key);
	if (expand_value <= 0)
	{
		expand_key_len = ft_strlen(expand_key);
		free(expand_key);
		return(expand_key_len);
	}
	else
	{
		expand_value_len = ft_strlen(expand_value);
		free(expand_key);
		return (expand_value_len);
	}
}
