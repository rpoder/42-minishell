/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:53:13 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 02:36:22 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	set_on(t_list **alst, char *key, char *value_to_modify)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(((t_expand *)tmp->content)->value);
		((t_expand *)tmp->content)->value = ft_alloc_and_fill(value_to_modify);
		return (true);
	}
	return (false);
}

int	set_expand(t_data *data, char *key, char *value_to_modify)
{
	if (set_on(&data->env, key, value_to_modify) == false)
	{
		if (set_on(&data->local_expands, key, value_to_modify) == false)
		{
			add_expand(data, &data->local_expands, ft_alloc_and_fill(key), ft_alloc_and_fill(value_to_modify));
			return (1);
		}
	}
	return (0);
}

//proteger !value
void	add_expand(t_data *data, t_list **alst, char *key, char *value) //recoit str allouees
{
	t_list		*lst;
	t_expand	*content;

	content = malloc(sizeof(t_expand));
	if (!content)
	{
		free(key);
		free(value);
		global_free(data, MALLOC_ERR);
	}
	content->key = key;
	content->value = get_muted_expand_value(value);
	free(value);
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}
