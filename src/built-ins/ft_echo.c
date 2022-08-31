/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/30 18:17:36 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data, char **args)
{
	int		i;
	bool	n_option;

	if (ft_strcmp(args[1], "ft_echo") != 0)
		return (-1);
	i = 2;
	n_option = false;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
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
