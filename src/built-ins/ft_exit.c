/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:17:52 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/31 16:43:08 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data *data, char **args)
{
	if (ft_strcmp(args[1], "ft_exit") != 0)
		return (-1);
	if (args[2] && !ft_str_isdigit(args[2]))
		ft_printf_fd("exit:\'%s\': not a valid identifier\n", 2, args[i]);
	global_free(data);
	exit(0);
}
