/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:17:52 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/03 22:24:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_data *data, char *exit_code)
{
	long int	li_exit_code;

	if (exit_code)
		li_exit_code = ft_atoli(exit_code);
	else
		li_exit_code = 0;
	ft_printf_fd("exit\n", 1);
	global_free(data, NO_ERR);
	if (ft_isint(li_exit_code))
		exit(li_exit_code);
	else
		exit (0);
}

int	ft_exit(t_data *data, char **args)
{
	if (ft_strcmp(args[1], "ft_exit") != 0)
		return (-1);
	if (args[2] && (!ft_str_isdigit(args[2]) || !ft_isint(ft_atoli(args[2]))))
	{
		ft_printf_fd("exit:\'%s\': numeric argument required\n", 2, args[2]);
		free_and_exit(data, NULL);
	}
	else if (ft_ptrlen(args) > 3)
	{
		ft_printf_fd("exit\n", 1);
		ft_printf_fd("exit: too many arguments\n", 2);
		set_expand(data, "?", "1");
		return (-1);
	}
	else if (args[2])
		free_and_exit(data, args[2]);
	else
		free_and_exit(data, NULL);
	return (0);
}
