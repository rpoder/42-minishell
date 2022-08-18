/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:31:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/18 16:23:55 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_expand(t_list **alst, t_list *last, t_list *tmp)
{
	if (!last)
		data->env = tmp->next;
	else
		last->next = tmp->next;
	del_expand(tmp->content);
}

static int	unset_from(t_list **alst, char *key_to_unset)
{
	t_list	*tmp;
	t_list	*last;
	bool	found;

	tmp = *alst;
	last = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, key_to_unset) == 0)
		{
			found = true;
			break;
		}
		last = tmp;
		tmp = tmp->next;
	}
	if (found == true)
		unset_expand(alst, last, tmp);
	return (found);
}

void	ft_unset(t_data *data, char *key_to_unset)
{
	bool	found;

	found = unset_from(&data->env, key_to_unset);
}
