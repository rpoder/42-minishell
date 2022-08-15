/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:16:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/12 09:09:20 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_last_before(t_data *data, char *key_to_find)
{
	t_list	*tmp;

	tmp = data->local_vars;
	while (tmp->next)
	{
		if (ft_strcmp(((t_shellvar *)tmp->next->content)->key, key_to_find) == 0)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_export(t_data *data, char *key_to_export)
{
	t_list	*tmp;
	t_list	*last;
	int		i;

	i = 0;
	tmp = data->local_vars;
	while (tmp)
	{
		if (ft_strcmp(((t_shellvar *)tmp->content)->key, key_to_export) == 0)
			break;
		i++;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (i == 0)
		data->local_vars = tmp->next;
	else
	{
		last = find_last_before(data, key_to_export);
		last->next = tmp->next;
	}
	tmp->next = NULL;
	ft_lstadd_back(&data->env, tmp);
}
