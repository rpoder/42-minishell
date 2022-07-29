/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:43:05 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/29 15:51:06 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;
	char	*first_key;
	char	*first_value;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	set_env(data, env);

	//add_shellvar(data->local_vars, alloc_and_fill("?"), alloc_and_fill("128"));
	//delete
	while (data->env)
	{
		printf("key: %s | value: %s\n", ((t_shellvar *)data->env->content)->key, ((t_shellvar *)data->env->content)->value);
		data->env = data->env->next;
	}
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

void	add_shellvar(t_list *alst, char *key, char *value)
{
	t_list		*lst;
	t_shellvar	*content;

	content = malloc(sizeof(t_shellvar));
	content->key = key;
	content->value = value;
	lst = ft_lstnew(content);
	printf("lst->key %s\n", ((t_shellvar *)lst->content)->key);
	ft_lstadd_back(&alst, lst);
}
