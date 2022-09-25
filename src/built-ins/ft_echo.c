/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 17:34:48 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data, char **args)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	while (args[i] && is_valid_flag(args[i]))
	{
		n_option = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n_option == false)
		ft_putchar_fd('\n', 1);
	set_expand(data, "?", "0");
	return (no_err);
}
