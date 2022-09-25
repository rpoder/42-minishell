/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_child_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:57:31 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 14:58:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tool_and_g_free(t_data *data, t_exec_tool *tool)
{
	free_exec_tool(&tool);
	global_free(data, malloc_err);
}

static void	set_back_stdout(t_data *data, t_exec_tool *tool)
{
	if (dup2(tool->fd_stdout, 1) < 0)
		free_tool_and_g_free(data, tool);
	close (tool->fd_stdout);
}

void	exec_no_child_builtin(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = (t_cmd_node *)cmd->content;
	tool->ret = open_and_set_fds(data->words, 0, cmd_node);
	if (tool->ret == malloc_err)
		free_tool_and_g_free(data, tool);
	else if (tool->ret == open_err)
		set_expand(data, "?", "1");
	if (tool->ret != no_err)
		return ;
	out_chevron_redir(data, cmd_node, tool);
	if (exec_builtins(data, (cmd_node)->cmd_tab, false, tool) != no_err)
		free_tool_and_g_free(data, tool);
	set_back_stdout(data, tool);
}
