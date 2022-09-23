/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:53 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 21:16:53 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *arg)
{
	int	ret;

	ret = -1;
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

int	builtins_cases(t_data *d, char **cmd_tab, int builtin, t_exec_tool *tool)
{
	int	ret;

	ret = NO_ERR;
	if (builtin == ENV)
		ret = ft_env(d, cmd_tab);
	else if (builtin == PWD)
		ret = ft_pwd(d, cmd_tab);
	else if (builtin == ECHO)
		ret = ft_echo(d, cmd_tab);
	else if (builtin == CD)
		ret = ft_cd(d, cmd_tab);
	else if (builtin == EXIT)
		ret = ft_exit(d, cmd_tab, tool);
	else if (builtin == EXPORT)
		ret = ft_export(d, cmd_tab);
	else if (builtin == UNSET)
		ret = ft_unset(d, cmd_tab);
	return (ret);
}

int	exec_builtins(t_data *d, char **cmd_tab, bool is_child, t_exec_tool *tool)
{
	int	ret;
	int	builtin;

	if (!cmd_tab[0])
		return (ERR_NOT_DEFINED);
	builtin = is_builtin(cmd_tab[0]);
	if (builtin < 0)
		return (ERR_NOT_DEFINED);
	ret = builtins_cases(d, cmd_tab, builtin, tool);
	if (ret == MALLOC_ERR || is_child == true)
	{
		if (tool)
			free_exec_tool(&tool);
		global_free(d, ret);
	}
	return (NO_ERR);
}
