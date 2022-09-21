/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:52:08 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/21 15:21:25 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_default_shlvl(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "SHLVL") == NULL)
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
