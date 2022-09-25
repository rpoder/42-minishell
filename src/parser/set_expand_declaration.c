/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expand_declaration.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:41:19 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 19:43:55 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_value_declaration(char *word, char **value)
{
	int		key_len;
	int		i;

	key_len = 0;
	while (word[key_len] != '=')
		key_len++;
	*value = malloc(sizeof(char) * (ft_strlen(word) - key_len + 1));
	if (!(*value))
		return (malloc_err);
	i = 0;
	key_len++;
	while (word[key_len])
	{
		(*value)[i] = word[key_len];
		key_len++;
		i++;
	}
	(*value)[i] = '\0';
	return (no_err);
}

static int	set_key_declaration(char *word, char **key)
{
	int		len;

	len = 0;
	while (word[len] != '=')
		len++;
	*key = malloc(sizeof(char) * (len + 1));
	if (!(*key))
		return (malloc_err);
	len = 0;
	while (word[len] != '=')
	{
		(*key)[len] = word[len];
		len++;
	}
	(*key)[len] = '\0';
	return (no_err);
}

int	set_expand_declaration(t_data *data, char *declaration)
{
	char	*key;
	char	*value;
	int		ret;

	ret = set_key_declaration(declaration, &key);
	if (ret != no_err)
		global_free(data, malloc_err);
	ret = set_value_declaration(declaration, &value);
	if (ret != no_err)
	{
		free(key);
		global_free(data, malloc_err);
	}
	set_malloced_expand(data, key, value);
	return (no_err);
}
