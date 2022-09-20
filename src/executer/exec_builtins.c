/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:53 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/20 19:27:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	int	ret;

	ret = 0;
	if (!arg)
		return (ret);
	if (ft_strcmp(arg, "echo") == 0)
		ret = ECHO;
	else if (ft_strcmp(arg, "env") == 0)
		ret = ENV;
	else if (ft_strcmp(arg, "pwd") == 0)
		ret = PWD;
	else if (ft_strcmp(arg, "cd") == 0)
		ret = CD;
	else if (ft_strcmp(arg, "exit") == 0)
		ret = EXIT;
	else if (ft_strcmp(arg, "export") == 0)
		ret = EXPORT;
	else if (ft_strcmp(arg, "unset") == 0)
		ret = UNSET;
	else
		ret = -1;
	return (ret);
}

int	exec_builtins(t_data *data, char **cmd_tab, bool exit)
{
	int	ret;
	int	builtin;

	ret = NO_ERR;
	if (!cmd_tab[0])
		return (ERR_NOT_DEFINED);
	builtin = is_builtin(cmd_tab[0]);
	if (builtin < 0)
		return (ERR_NOT_DEFINED);
	if (builtin == ENV)
		ret = ft_env(data, cmd_tab);
	else if (builtin == PWD)
		ret = ft_pwd(data, cmd_tab);
	else if (builtin == ECHO)
		ret = ft_echo(data, cmd_tab);
	else if (builtin == CD)
		ret = ft_cd(data, cmd_tab);
	else if (builtin == EXIT)
		ret = ft_exit(data, cmd_tab);
	else if (builtin == EXPORT)
		ret = ft_export(data, cmd_tab);
	else if (builtin == UNSET)
		ret = ft_unset(data, cmd_tab);
	else
		ret = ERR_NOT_DEFINED;
	if (ret == MALLOC_ERR)
	{
		ft_printf_fd("child: ", 2);
		global_free(data, MALLOC_ERR);
	}
	if (exit == true)
		global_free(data, ERR_NOT_DEFINED);
	if (ret == NO_ERR || ret == PARSING_ERR)
		return (NO_ERR);
}
