/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:33:22 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/18 16:15:08 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data, char **args)
{
	int		ret;
	char	*home_expand_value;
	printf("IN BUILTINS CD\n");

	home_expand_value = get_expand_value(data, "HOME");
	if (!home_expand_value && !args[1])
		return (NO_ERR);
	else if (home_expand_value && !args[1])
	{
		ret = chdir(home_expand_value);
		if (ret != 0)
		{
			ft_printf_fd("minilsshell: cd: ", 2);
			perror(home_expand_value);
		}
	}
	else if (args[1])
	{
		printf("%s\n", args[1]);
		ret = chdir(args[1]);
		if (ret != 0)
		{
			ft_printf_fd("minilsshell: cd: ", 2);
			perror(args[1]);
		}
	}

	return (NO_ERR);
}
