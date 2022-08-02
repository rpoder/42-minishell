/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/02 11:22:22 by ronanpoder       ###   ########.fr       */
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
	set_env(env);
	printf("data init=%p\n", data);
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

void	set_env(char **env)
{
	int	i;

	i = 0;
	printf("data set_env=%p\n", data);
	if (!env)
		data->env = NULL;
	else
	{
		while (env[i])
		{
			add_shellvar(&data->env, get_env_key(env[i]), get_env_value(env[i]));
			printf("env %p\n", &data->env);
			i++;
		}
	}
}

t_quotes	init_quotes(void)
{
	t_quotes	quotes;

	quotes.sgl_quote = false;
	quotes.dbl_quote = false;
	return (quotes);
}
