/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:44:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/13 22:21:47 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (NULL);
}

char	*get_expand_key(char *str, int i)
{
	int		j;
	char	*expand_key;

	j = 0;
	expand_key = malloc((expand_key_len(str, i) + 1) * sizeof(char));
	if (!expand_key)
		return (NULL);
	while (str[i + j] && !is_expand_suffix(str[i + j], j)
		&& !is_expand_separator(str[i + j]))
	{
		expand_key[j] = str[i + j];
		j++;
	}
	expand_key[j] = '\0';
	return (expand_key);
}
