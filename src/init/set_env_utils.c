/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:52:08 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 17:24:41 by mpourrey         ###   ########.fr       */
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
		return (malloc_err);
	if (set_malloced_value_expand(data, "SHLVL", tmp) == malloc_err)
	{
		free(tmp);
		return (malloc_err);
	}
	return (no_err);
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
			return (malloc_err);
		value = ft_alloc_and_fill("1");
		if (!value)
			return (free(key), malloc_err);
		add_expand(data, &data->env, key, value);
	}
	else
	{
		if (increment_shlvl(data, shlvl_value) != no_err)
			return (malloc_err);
	}
	return (no_err);
}

static int	add_default_underscore(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "_") == NULL)
	{
		key = ft_alloc_and_fill("_");
		if (!key)
			return (malloc_err);
		if (set_path(data, &value) == malloc_err)
		{
			free(key);
			return (malloc_err);
		}
		add_expand(data, &data->env, key, value);
	}
	return (no_err);
}

static int	add_default_pwd(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "PWD") == NULL)
	{
		key = ft_alloc_and_fill("PWD");
		if (!key)
			return (malloc_err);
		if (set_path(data, &value) == malloc_err)
		{
			free(key);
			return (malloc_err);
		}
		add_expand(data, &data->env, key, value);
	}
	return (no_err);
}

int	add_default_expands_to_env(t_data *data)
{
	int	ret;

	ret = add_default_pwd(data);
	ret = add_default_underscore(data);
	ret = add_default_shlvl(data);
	return (ret);
}
