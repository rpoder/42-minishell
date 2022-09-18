/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:53 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/17 17:05:25 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_data *data, char **cmd_tab)
{
	if (ft_strcmp(cmd_tab[0], "env") == 0)
	{
		ft_env(data, cmd_tab);
		return (0);
	}
	else if (ft_strcmp(cmd_tab[0], "pwd") == 0)
	{
		ft_pwd(data, cmd_tab);
		return (0);
	}
	else if (ft_strcmp(cmd_tab[0], "cd") == 0)
	{
		ft_cd(data, cmd_tab);
		return (0);
	}
	else if (ft_strcmp(cmd_tab[0], "exit") == 0)
	{
		ft_exit(data, cmd_tab);
		return (0);
	}
	else if (ft_strcmp(cmd_tab[0], "export") == 0)
	{
		ft_export(data, cmd_tab);
		return (0);
	}
	else if (ft_strcmp(cmd_tab[0], "unset") == 0)
	{
		ft_unset(data, cmd_tab);
		return (0);
	}
	return (-1);
}
