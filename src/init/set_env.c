/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:24:39 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 20:17:07 by mpourrey         ###   ########.fr       */
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
		global_free(data, malloc_err);
	value = get_env_value(arg);
	if (!value)
	{
		free(key);
		global_free(data, malloc_err);
	}
	add_expand(data, &data->env, key, value);
}

void	set_env(t_data *data, char **env)
{
	int		i;
	char	*env_key;
	char	*env_value;

	env_key = NULL;
	env_value = NULL;
	i = 0;
	if (env && !env[0])
	{
		if (add_default_expands_to_env(data) != no_err)
			global_free(data, malloc_err);
	}
	else
	{
		while (env[i])
		{
			set_one_env_line(data, env[i], env_key, env_value);
			i++;
		}
		if (add_default_shlvl(data) == malloc_err)
			global_free(data, malloc_err);
	}
}
