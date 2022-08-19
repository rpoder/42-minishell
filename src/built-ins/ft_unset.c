/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:31:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/19 10:24:12 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_expand(t_list **alst, t_list *last, t_list *tmp)
{
	if (!alst)
		*alst = tmp->next;
	else
	{
		if (last)
			last->next = tmp->next;
		else
			*alst = tmp->next;
	}
	del_t_expand(tmp);
}

static int	unset_from(t_list **alst, char *key_to_unset)
{
	t_list	*tmp;
	t_list	*last;

	tmp = *alst;
	last = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, key_to_unset) == 0)
			break;
		last = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		unset_expand(alst, last, tmp);
		return (true);
	}
	return (false);
}

void	ft_unset(t_data *data, char *key_to_unset)
{
	bool	found;

	found = unset_from(&data->local_expands, key_to_unset);
	if (!found)
		unset_from(&data->env, key_to_unset);
}
