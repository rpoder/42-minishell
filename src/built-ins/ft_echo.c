/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/22 17:42:28 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args, int fd)
{
	int		i;
	bool	n_option;

	if (ft_strcmp(args[1], "echo") != 0)
		return (-1);
	i = 2;
	n_option = false;
	if (ft_strcmp(args[i], "-n") == 0)
	{
		n_option = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	if (n_option == false)
		ft_putchar_fd('\n', fd);
	//exit
	return (0);
}
