/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:40:53 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 20:24:16 by mpourrey         ###   ########.fr       */
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
		ret = e_echo;
	else if (ft_strcmp(arg, "env") == 0)
		ret = e_env;
	else if (ft_strcmp(arg, "pwd") == 0)
		ret = e_pwd;
	else if (ft_strcmp(arg, "cd") == 0)
		ret = e_cd;
	else if (ft_strcmp(arg, "exit") == 0)
		ret = e_exit;
	else if (ft_strcmp(arg, "export") == 0)
		ret = e_export;
	else if (ft_strcmp(arg, "unset") == 0)
		ret = e_unset;
	else
		ret = -1;
	return (ret);
}

static int	builtins_cases(t_data *d, char **cmd_tab,
	int builtin, t_exec_tool *tool)
{
	int	ret;

	ret = no_err;
	if (builtin == e_env)
		ret = ft_env(d, cmd_tab);
	else if (builtin == e_pwd)
		ret = ft_pwd(d);
	else if (builtin == e_echo)
		ret = ft_echo(d, cmd_tab);
	else if (builtin == e_cd)
		ret = ft_cd(d, cmd_tab);
	else if (builtin == e_exit)
		ret = ft_exit(d, cmd_tab, tool);
	else if (builtin == e_export)
		ret = ft_export(d, cmd_tab);
	else if (builtin == e_unset)
		ret = ft_unset(d, cmd_tab);
	return (ret);
}

int	exec_builtins(t_data *d, char **cmd_tab, bool is_child, t_exec_tool *tool)
{
	int	ret;
	int	builtin;

	if (!cmd_tab[0])
		return (err_not_defined);
	builtin = is_builtin(cmd_tab[0]);
	if (builtin < 0)
		return (err_not_defined);
	ret = builtins_cases(d, cmd_tab, builtin, tool);
	if (ret == malloc_err || is_child == true)
	{
		if (tool)
			free_exec_tool(&tool);
		global_free(d, ret);
	}
	return (no_err);
}
