/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/11 17:41:21 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args, int fd)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	if (ft_strcmp(args[i], "-n") == 0)
	{
		n_option = true;
		i++;
	}
	while(args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	if (n_option == false)
		ft_putchar_fd('\n', fd);
}
