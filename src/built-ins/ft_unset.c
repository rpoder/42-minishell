/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:31:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 15:33:27 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_expand_ptr(t_list **alst, t_list *last, t_list *tmp)
{
	if (alst != NULL && tmp != NULL)
	{
		if (*alst == NULL || last == NULL)
			*alst = tmp->next;
		else
			last->next = tmp->next;
	}
	ft_lstdelone(tmp, &del_expand);
}

static bool	unset_from(t_list **alst, char *key_to_unset)
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
		move_expand_ptr(alst, last, tmp);
		return (true);
	}
	return (false);
}

int	ft_unset(t_data *data, char **args)
{
	int		i;
	int		ret;

	ret = NO_ERR;
	i = 1;
	while (args[i])
	{
		if (!is_valid_expand_key(args[i]))
		{
			ft_printf_fd("unset:\'%s\': not a valid identifier\n", 2, args[i]);
			ret = PARSING_ERR;
		}
		else if (unset_from(&data->local_expands, args[i]) == false)
			unset_from(&data->env, args[i]);
		i++;
	}
	if (ret == NO_ERR)
		set_expand(data, "?", "0");
	else
		set_expand(data, "?", "1");
	return (ret);
}
