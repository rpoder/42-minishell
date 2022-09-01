/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:17:52 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/01 11:25:03 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data, char **args)
{
	if (ft_strcmp(args[1], "ft_exit") != 0)
		return (-1);
	if (args[2] && ft_str_isdigit(args[2]))
	{
		ft_printf_fd("exit:\'%s\': numeric argument required\n", 2, args[2]);
		return (-1);
	}
	else if (ft_tablen(args) > 3)
	{
		ft_printf_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	ft_printf_fd("exit\n", 1);
	global_free(data, NO_ERR);
	if (args[2])
		exit(ft_atoi(args[2]));
	else
		exit(0);
}
