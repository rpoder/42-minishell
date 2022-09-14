/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/14 10:23:09 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data, char **args)
{
	int		i;
	bool	n_option;

	if (ft_strcmp(args[0], "echo") != 0)
		return (-1);
	i = 1;
	n_option = false;
	while (args[i] && args[i][0] && args[i][0] == '-' &&
		args[i][1] && args[i][1] == 'n')
	{
		n_option = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (n_option == false)
		ft_putchar_fd('\n', 1);
	set_expand(data, "?", "0");
	return (0);
}
