/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:24:39 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/26 14:37:27 by ronanpoder       ###   ########.fr       */
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
	//proteger
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
		global_free();
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

void	set_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	if (!env)
		data->env = NULL;
	else
	{
		while (env[i])
		{
			ft_add_expand(&data->env, get_env_key(env[i]), get_env_value(env[i]), false);
			//printf("env |%s|\n", env[i]);
			i++;
		}
	}
	// t_list *tmp;
	// tmp = data->env;
	// while (tmp)
	// {
	// 	printf("key = %s |	value = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }
}
