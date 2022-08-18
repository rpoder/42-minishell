/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:45:13 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/17 12:06:08 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data, int fd)
{
	t_list	*tmp;

	if (!data->env)
		return;
	tmp = data->env;
	while (tmp)
	{
		ft_putstr_fd(((t_expand *)tmp->content)->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(((t_expand *)tmp->content)->value, fd);
		ft_putchar_fd('\n', fd);
		tmp = tmp->next;
	}
}
