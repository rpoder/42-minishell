/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:53:13 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 18:49:27 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_on(t_list **alst, char *key, char *value_to_modify)
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
		((t_expand *)tmp->content)->value = alloc_and_fill(value_to_modify);
		return (true);
	}
	return (false);
}

int	ft_set_expand(t_data *data, char *key, char *value_to_modify)
{
	bool	found;

	found = false;
	found = set_on(&data->local_expands, key, value_to_modify);
	if (!found)
		found = set_on(&data->env, key, value_to_modify);
	return (found);
}

//proteger !value
void	ft_add_expand(t_list **alst, char *key, char *value, bool manual_add) //recoit str allouees
{
	t_list		*lst;
	t_expand	*content;

	content = malloc(sizeof(t_expand));
	if (!content)
		global_free();
	content->key = key;
	content->value = get_muted_expand_value(value);
	free(value);
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}
