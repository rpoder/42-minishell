/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/05 16:58:33 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*add_return_value_expand(t_data *data)
{
	char	*expand_key;
	char	*expand_value;

	expand_key = alloc_and_fill("?");
	if (!expand_key)
		return (NULL);
	expand_value = alloc_and_fill("0");
	if (!expand_value)
	{
		free(expand_key);
		return (NULL);
	}
	add_expand(data, &data->local_expands, expand_key, expand_value);
	return (data->local_expands);
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
	data->local_expands = add_return_value_expand(data);
	if (!data->local_expands)
		global_free(data, MALLOC_ERR);
	data->prompt_line = alloc_and_fill(prompt_line);
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
