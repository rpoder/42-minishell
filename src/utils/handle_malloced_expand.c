/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_malloced_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:03:05 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 17:41:28 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_malloced_exp_on(t_list **alst, char *key, char *new_value)
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
		free(key);
		free(((t_expand *)tmp->content)->value);
		((t_expand *)tmp->content)->value = new_value;
		return (true);
	}
	return (false);
}

int	set_malloced_expand(t_data *data, char *key, char *new_value)
{
	if (set_malloced_exp_on(&data->env, key, new_value) == false)
	{
		if (set_malloced_exp_on(&data->local_expands,
				key, new_value) == false)
		{
			add_expand(data, &data->local_expands,
				key, new_value);
			return (1);
		}
	}
	return (0);
}

static bool	set_malloced_value_exp_on(t_list **alst, char *key, char *new_value)
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
		((t_expand *)tmp->content)->value = new_value;
		return (true);
	}
	return (false);
}

int	set_malloced_value_expand(t_data *data, char *key, char *new_value)
{
	char	*tmp;

	if (set_malloced_value_exp_on(&data->env, key, new_value) == false)
	{
		if (set_malloced_value_exp_on(&data->local_expands,
				key, new_value) == false)
		{
			tmp = ft_alloc_and_fill(key);
			if (!tmp)
				return (malloc_err);
			add_expand(data, &data->local_expands,
				key, new_value);
			return (1);
		}
	}
	return (0);
}
