/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:01:38 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 15:04:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_and_alloc_value(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len] && str[len] == '=')
		len++;
	value = malloc(sizeof(char) * (ft_strlen(str + len) + 1));
	if (!value)
		return (NULL);
	j = 0;
	i = len;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

char	*trim_and_alloc_key(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	set_trim_alloc_keyvalue(char *arg, char **key, char **value)
{
	*key = trim_and_alloc_key(arg);
	if (!(*key))
		return (malloc_err);
	*value = trim_and_alloc_value(arg);
	if (!*(value))
		return (malloc_err);
	return (no_err);
}
