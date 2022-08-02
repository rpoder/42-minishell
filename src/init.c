/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/02 11:35:48 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	//proteger
	data->local_vars = NULL;
	data->env = NULL;
	set_env(data, env);
	add_shellvar(&data->local_vars, alloc_and_fill("?"), alloc_and_fill("127"));
	//delete
	// t_list *tmp;
	// tmp = data->env;
	// while (tmp)
	// {
	// 	printf("key: %s |	value: %s\n", ((t_shellvar *)tmp->content)->key, ((t_shellvar *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	data->prompt_line = NULL;
	return (data);
}

t_quotes	init_quotes(void)
{
	t_quotes	quotes;

	quotes.sgl_quote = false;
	quotes.dbl_quote = false;
	return (quotes);
}
