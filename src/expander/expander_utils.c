/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:05 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/31 16:35:02 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_expand_to_interpret(char *str, int i, t_quotes *quotes)
{
	if (!str[i + 1] || is_separator(str[i + 1]))
		return (0);
	if (quotes->dbl_quote)
		return (1);
	else if (quotes->sgl_quote)
		return (0);
	return (1);
}

char	*get_expand_value(t_data *data, char *expand_key)
{
	t_list	*tmp;

	tmp = data->local_expands;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, expand_key) == 0)
			return (((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}
	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, expand_key) == 0)
			return (((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (NULL); ////////////////////
}

char	*get_expand_key(char *str, int i)
{
	int		j;
	char	*expand_key;

	j = 0;
	expand_key = malloc((expand_key_len(str, i) + 1) * sizeof(char));
	if (!expand_key)
		return (NULL);
	while (str[i + j] && !is_separator(str[i + j])) //is_expand_separator, ajouter tout sauf alpha et '_'
	{
		expand_key[j] = str[i + j];
		j++;
	}
	expand_key[j] = '\0';
	return (expand_key);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '$' || c == '|' || c == '\"' || c == '\''
		|| c == '<' || c == '>')
		return (1);
	return (0);
}
