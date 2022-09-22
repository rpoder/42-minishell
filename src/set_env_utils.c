/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:52:08 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 21:54:45 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_default_shlvl(t_data *data)
{
	char	*key;
	char	*value;
	char	*shlvl_value;
	int		shlvl_value_int;

	shlvl_value = get_expand_value(data, "SHLVL");
	if (shlvl_value == NULL)
	{
		key = ft_alloc_and_fill("SHLVL");
		if (!key)
			return (MALLOC_ERR);
		value = ft_alloc_and_fill("1");
		if (!value)
		{
			free(key);
			return (MALLOC_ERR);
		}
		add_expand(data, &data->env, key, value);
	}
	else
	{
		shlvl_value_int = ft_atoi(shlvl_value);
		shlvl_value_int++;
		set_expand(data, "SHLVL", ft_itoa(shlvl_value_int));
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
