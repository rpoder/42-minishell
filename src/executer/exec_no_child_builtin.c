/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_child_builtin_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:25:42 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 15:25:57 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tool_and_g_free(t_data *data, t_exec_tool *tool)
{
	free_exec_tool(&tool);
	global_free(data, DUP_ERR);
}

static void	set_back_stdout(t_data *data, t_exec_tool *tool)
{
	if (dup2(tool->fd_stdout, 1) < 0)
		free_tool_and_g_free(data, tool);
}

static void	save_stdout(t_data *data, t_exec_tool *tool)
{
	tool->fd_stdout = dup(1);
	if (tool->fd_stdout < 0)
		free_tool_and_g_free(data, tool);
}

void	exec_no_child_builtin(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char	**env_tab;

	tool->ret = open_and_set_fds(data->words, 0, (t_cmd_node *)cmd->content);
	if (tool->ret == MALLOC_ERR)
		free_tool_and_g_free(data, tool);
	else if (tool->ret != NO_ERR)
		return ;
	save_stdout(data, tool);
	env_tab = get_env_tab(data);
	if (!env_tab)
		free_tool_and_g_free(data, tool);
	out_chevron_redir(data, (t_cmd_node *)cmd->content, tool);
	if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, false) != NO_ERR)
	{
		ft_free_tab(&env_tab);
		free_tool_and_g_free(data, tool);
	}
	ft_free_tab(&env_tab);
	set_back_stdout(data, tool);
}
