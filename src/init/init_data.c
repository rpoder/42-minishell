/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 20:12:14 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_error_expand_to_local(t_data *data)
{
	char	*key;
	char	*value;

	key = ft_alloc_and_fill("?");
	if (!key)
		return (malloc_err);
	value = ft_alloc_and_fill("0");
	if (!value)
	{
		free(key);
		return (malloc_err);
	}
	add_expand(data, &data->local_expands, key, value);
	return (no_err);
}

static int	add_path_to_local(t_data *data)
{
	char	*key;
	char	*value;

	if (get_expand_value(data, "PATH") == NULL)
	{
		key = ft_alloc_and_fill("PATH");
		if (!key)
			return (malloc_err);
		value = ft_strsjoin(3, ENV_DFL_PATH_1, ENV_DFL_PATH_2, ENV_DFL_PATH_3);
		if (!value)
		{
			free(key);
			return (malloc_err);
		}
		add_expand(data, &data->local_expands, key, value);
	}
	return (no_err);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		global_free(data, malloc_err);
	data->env = NULL;
	data->local_expands = NULL;
	set_env(data, env);
	data->prompt_line = NULL;
	data->expanded_line = NULL;
	data->words = NULL;
	data->cmds = NULL;
	if (add_error_expand_to_local(data) != no_err
		|| add_path_to_local(data) != no_err)
		global_free(data, malloc_err);
	return (data);
}
