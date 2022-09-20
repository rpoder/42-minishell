/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:53 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/20 15:10:30 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_data *data, char **cmd_tab)
{
	int	ret;

	ret = NO_ERR;
	if (!cmd_tab[0])
		return (ERR_NOT_DEFINED);
	if (ft_strcmp(cmd_tab[0], "env") == 0)
		ret = ft_env(data, cmd_tab);
	else if (ft_strcmp(cmd_tab[0], "pwd") == 0)
		ret = ft_pwd(data, cmd_tab);
	else if (ft_strcmp(cmd_tab[0], "cd") == 0)
		ret = ft_cd(data, cmd_tab);
	else if (ft_strcmp(cmd_tab[0], "exit") == 0)
		ret = ft_exit(data, cmd_tab);
	else if (ft_strcmp(cmd_tab[0], "export") == 0)
		ret = ft_export(data, cmd_tab);
	else if (ft_strcmp(cmd_tab[0], "unset") == 0)
		ret = ft_unset(data, cmd_tab);
	else
		ret = ERR_NOT_DEFINED;
	if (ret == MALLOC_ERR)
	{
		ft_printf_fd("child: ", 2);
		global_free(data, MALLOC_ERR);
	}
	// exit
	return (ret);
}
