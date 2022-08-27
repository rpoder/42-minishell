/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:31:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/27 16:43:30 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_err(char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (args[i])
	{
		if (check_t_expand_key_input(args[i]) != 0)
		{
			ft_putstr_fd("unset:\'", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			ret = 1;
		}
		i++;
	}
	return (ret);
}

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
	del_one_expand(tmp);
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
			break ;
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

int	ft_unset(t_data *data, char **args)
{
	int		i;
	bool	found;

	if (ft_strcmp(args[1], "unset") != 0)
		return (-1);
	if (check_unset_err(args + 2) != 0)
	{
		//modify $? to "1"
		return (-1);
	}
	i = 2;
	while (args[i])
	{
		found = false;
		found = unset_from(&data->local_expands, args[i]);
		if (!found)
			unset_from(&data->env, args[i]);
		i++;
	}
	return (0);
}
