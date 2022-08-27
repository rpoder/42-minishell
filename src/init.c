/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/28 00:57:20 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env, char *prompt_line)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		global_free(data);
	data->env = NULL;
	set_env(data, env);
	data->local_expands = NULL;
	add_expand(data, &data->local_expands, alloc_and_fill("?"), alloc_and_fill("127"));
	data->prompt_line = alloc_and_fill(prompt_line); //proteger
	data->expanded_line = NULL;
	data->tokens = NULL;
	return (data);
}

t_quotes	*set_quotes(char c, t_quotes *quotes)
{
	if (c == '\"')
		quotes->dbl_quote = !quotes->dbl_quote;
	if (c == '\'')
		quotes->sgl_quote = !quotes->sgl_quote;
	return (quotes);
}

t_quotes	*clear_quotes(t_quotes *quotes)
{
	quotes->sgl_quote = false;
	quotes->dbl_quote = false;
	return (quotes);
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
