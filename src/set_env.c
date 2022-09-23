/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:24:39 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 21:17:36 by rpoder           ###   ########.fr       */
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
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_env_value(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*value;

	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	if (str[j] + 1)
		j++;
	len = 0;
	while (str[j + len])
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[j])
	{
		value[i] = str[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

static void	set_one_env_line(t_data *data, char *arg, char *key, char *value)
{
	key = get_env_key(arg);
	if (!key)
		global_free(data, MALLOC_ERR);
	value = get_env_value(arg);
	if (!value)
	{
		free(key);
		global_free(data, MALLOC_ERR);
	}
	add_expand(data, &data->env, key, value);
}

void	set_env(t_data *data, char **env)
{
	int		i;
	char	*env_key;
	char	*env_value;

	i = 0;
	if (env && !env[0])
	{
		if (add_default_expands_to_env(data) != NO_ERR)
			global_free(data, MALLOC_ERR);
	}
	else
	{
		while (env[i])
		{
			set_one_env_line(data, env[i], env_key, env_value);
			i++;
		}
		if (add_default_shlvl(data) == MALLOC_ERR)
			global_free(data, MALLOC_ERR);
	}
}
