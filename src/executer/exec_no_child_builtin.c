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
	close (tool->fd_stdout);
}

void	exec_no_child_builtin(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	tool->ret = open_and_set_fds(data->words, 0, (t_cmd_node *)cmd->content);
	if (tool->ret == MALLOC_ERR)
		free_tool_and_g_free(data, tool);
	else if (tool->ret != NO_ERR)
		return ;
	out_chevron_redir(data, (t_cmd_node *)cmd->content, tool);
	if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, false) != NO_ERR)
		free_tool_and_g_free(data, tool);
	set_back_stdout(data, tool);
}
