/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:52:08 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 21:46:48 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	increment_shlvl(t_data *data, char *shlvl_value)
{
	char	*tmp;
	int		shlvl_value_int;

	shlvl_value_int = ft_atoi(shlvl_value);
	shlvl_value_int++;
	tmp = ft_itoa(shlvl_value_int);
	if (!tmp)
		return (MALLOC_ERR);
	set_malloced_expand(data, "SHLVL", tmp);
	return (NO_ERR);
}

int	add_default_shlvl(t_data *data)
{
	char	*key;
	char	*value;
	char	*shlvl_value;
	char	*tmp;

	shlvl_value = get_expand_value(data, "SHLVL");
	if (!shlvl_value)
	{
		key = ft_alloc_and_fill("SHLVL");
		if (!key)
			return (MALLOC_ERR);
		value = ft_alloc_and_fill("1");
		if (!value)
			return (free(key), MALLOC_ERR);
		add_expand(data, &data->env, key, value);
	}
	else
	{
		if (increment_shlvl(data, shlvl_value) != NO_ERR)
			return (MALLOC_ERR);
	}
	return (NO_ERR);
}

static int	add_default_underscore(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "_") == NULL)
	{
		key = ft_alloc_and_fill("_");
		if (!key)
			return (MALLOC_ERR);
		if (set_path(data, &value) == MALLOC_ERR)
		{
			free(key);
			return (MALLOC_ERR);
		}
		add_expand(data, &data->env, key, value);
	}
	return (NO_ERR);
}

static int	add_default_pwd(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "PWD") == NULL)
	{
		key = ft_alloc_and_fill("PWD");
		if (!key)
			return (MALLOC_ERR);
		if (set_path(data, &value) == MALLOC_ERR)
		{
			free(key);
			return (MALLOC_ERR);
		}
		add_expand(data, &data->env, key, value);
	}
	return (NO_ERR);
}

int	add_default_expands_to_env(t_data *data)
{
	int	ret;

	ret = add_default_pwd(data);
	ret = add_default_underscore(data);
	ret = add_default_shlvl(data);
	return (ret);
}
