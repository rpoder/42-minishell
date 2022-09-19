/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:16:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/19 20:10:33 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_to_env(t_data *data, char *key_to_export)
{
	t_list	*tmp;
	t_list	*last;

	if (!data->local_expands)
		return ;
	tmp = data->local_expands;
	last = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, key_to_export) == 0)
			break ;
		last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (last == NULL)
		data->local_expands = tmp->next;
	else
		last->next = tmp->next;
	tmp->next = NULL;
	ft_lstadd_back(&data->env, tmp);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		ret;

	ret = NO_ERR;
	i = 1;
	while (args[i])
	{
		if (!is_valid_expand_key(args[i]))
		{
			ft_printf_fd("export:\'%s\': not a valid identifier\n", 2, args[i]);
			ret = PARSING_ERR;
		}
		else
			move_to_env(data, args[i]);
		i++;
	}
	if (ret == NO_ERR)
		set_expand(data, "?", "0");
	else
		set_expand(data, "?", "1");
	return (ret);
}
