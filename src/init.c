/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/17 12:05:47 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		global_free();
	data->env = NULL;
	set_env(data, env);
	data->local_expands = NULL;
	add_expand(&data->local_expands, alloc_and_fill("?"), alloc_and_fill("127"));
	data->prompt_line = NULL;
	data->tokens = NULL;
	return (data);
}

t_quotes	*init_quotes(void)
{
	t_quotes	*quotes;

	quotes = malloc(sizeof(t_quotes));
	// proteger
	quotes->sgl_quote = false;
	quotes->dbl_quote = false;
	return (quotes);
}
