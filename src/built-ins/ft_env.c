/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:45:13 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/30 18:02:50 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, char **args)
{
	t_list	*tmp;

	if (ft_strcmp(args[1], "ft_env") != 0)
		return ;
	if (args[2])
	{
		ft_putstr_fd("env:\'", 2);
		ft_putstr_fd(args[2], 2);
		ft_putstr_fd("\': not such file or directory\n", 2);
		set_expand(data, "?", "127");
		return ;
	}
	if (!data->env)
		return ;
	tmp = data->env;
	while (tmp)
	{
		ft_putstr_fd(((t_expand *)tmp->content)->key, 1);
		ft_putchar_fd('=', 1);
		if (((t_expand *)tmp->content)->value)
			ft_putstr_fd(((t_expand *)tmp->content)->value, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	set_expand(data, "?", "0");
}
