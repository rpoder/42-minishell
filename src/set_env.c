/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:24:39 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/02 11:22:59 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_key(char *str)
{
	int		len;
	int		i;
	char	*key;

	len = 0;
	while (str[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	// proteger
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	//printf("key : %s\n", key);
	return (key);
}

char	*get_env_value(char *str)
{
	int		len;
	int		i;
	char	*value;

	len = 0;
	while (*str != '=')
		str++;
	if (str + 1)
		str++;
	while (str[len])
		len++;
	value = malloc(sizeof(char) * (len + 1));
	// proteger
	i = 0;
	while (i < len)
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}


