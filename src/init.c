/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/12 15:01:16 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_error_expand_to_local(t_data *data)
{
	char	*key;
	char	*value;

	key = ft_alloc_and_fill("?");
	if (!key)
		return (MALLOC_ERR);
	value = ft_alloc_and_fill("0");
	if (!value)
	{
		free(key);
		return (MALLOC_ERR);
	}
	add_expand(data, &data->local_expands, key, value);
	return (NO_ERR);
}

static int	add_path_to_local(t_data *data, char **env)
{
	char	*key;
	char	*value;

	if (env && !env[0])
	{
		if (get_expand_value(data, "PATH") == NULL)
		{
			key = ft_alloc_and_fill("PATH");
			if (!key)
				return (MALLOC_ERR);
			value = ft_alloc_and_fill(ENV_DEFAULT_PATH);
			if (!value)
			{
				free(key);
				return (MALLOC_ERR);
			}
			add_expand(data, &data->local_expands, key, value);
		}
	}
	return (NO_ERR);
}

t_data	*init_data(char **env, char *prompt_line)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		global_free(data, MALLOC_ERR);
	data->env = NULL;
	set_env(data, env);
	data->local_expands = NULL;
	data->prompt_line = NULL;
	data->expanded_line = NULL;
	data->words = NULL;
	data->cmds = NULL;
	if (add_error_expand_to_local(data) != NO_ERR || add_path_to_local(data, env) != NO_ERR)
		global_free(data, MALLOC_ERR);
	data->prompt_line = ft_alloc_and_fill(prompt_line);
	if (!data->prompt_line)
		global_free(data, MALLOC_ERR);
	return (data);
}

void	set_quotes(char c, t_quotes *quotes)
{
	if (c == '\"')
		quotes->dbl_quote = !quotes->dbl_quote;
	if (c == '\'')
		quotes->sgl_quote = !quotes->sgl_quote;
}

void	clear_quotes(t_quotes *quotes)
{
	quotes->sgl_quote = false;
	quotes->dbl_quote = false;
}

t_quotes	*init_quotes(void)
{
	t_quotes	*quotes;

	quotes = malloc(sizeof(t_quotes));
	if (quotes == NULL)
		return (NULL);
	clear_quotes(quotes);
	return (quotes);
}
