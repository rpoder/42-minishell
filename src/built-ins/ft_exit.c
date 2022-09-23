/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:17:52 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 23:22:23 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is8bits(long int num)
{
	if (num > 0 || num < 255)
		return (0);
	return (1);
}

static void	free_and_exit(t_data *data, t_exec_tool *tool, char *exit_code)
{
	char	bits_exit_code;
	char	*tmp;

	if (exit_code)
		bits_exit_code = (char)ft_atoi(exit_code);
	else
		bits_exit_code = 0;
	tmp = ft_itoa((int)bits_exit_code);
	if (!tmp)
	{
		if (tool)
			free_exec_tool(&tool);
		global_free(data, MALLOC_ERR);
	}
	ft_printf_fd("exit\n", 1);
	set_malloced_expand(data, "?", tmp);
	if (tool)
		free_exec_tool(&tool);
	global_free(data, NO_ERR);
}

int	ft_exit(t_data *data, char **args, t_exec_tool *tool)
{
	if ((args[1] && (!ft_str_isdigit(args[1])) || !ft_isint(ft_atoli(args[1]))))
	{
		ft_printf_fd("exit:\'%s\': numeric argument required\n", 2, args[1]);
		free_and_exit(data, tool, "2");
	}
	else if (ft_tablen(args) > 2)
	{
		ft_printf_fd("exit: too many arguments\n", 2);
		set_expand(data, "?", "1");
		return (-1);
	}
	else if (args[1])
		free_and_exit(data, tool, args[1]);
	else
		free_and_exit(data, tool, NULL);
	return (NO_ERR);
}
