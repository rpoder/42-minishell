/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:17:45 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 19:49:15 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_data *data, t_list *cmd,
	char **env_tab, t_exec_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = ((t_cmd_node *)cmd->content);
	default_all_sigs();
	if (!is_last_cmd(cmd))
		redirect_to_pipe(data, tool);
	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	free_exec_tool(&tool);
	if (cmd_node->cmd_tab[0])
	{
		if (exec_builtins(data, cmd_node->cmd_tab, true, tool) != no_err)
		{
			if (execve(cmd_node->path, cmd_node->cmd_tab, env_tab) != 0)
			{
				ft_printf_fd("%s: command not found\n", 2, cmd_node->cmd_tab[0]);
				if (!is_redir_err_or_chevron_err(data))
					set_expand(data, "?", "127");
			}
		}
	}
	ft_free_tab(&env_tab);
	global_free(data, no_err);
}

void	create_and_exec_child(t_data *data, t_list *cmd,
	char **env_tab, t_exec_tool *tool)
{
	handle_fork(data, tool);
	if (tool->fork_ret[tool->i] == 0)
		exec_child(data, cmd, env_tab, tool);
}

void	exec_children(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	int		lexer_len;
	char	**env_tab;

	lexer_len = 0;
	env_tab = get_env_tab(data);
	if (!env_tab)
		free_exec_children(data, tool, NULL);
	while (cmd)
	{
		tool->ret = open_and_set_fds(data->words, lexer_len,
				(t_cmd_node *)cmd->content);
		if (tool->ret == malloc_err)
			free_exec_children(data, tool, env_tab);
		else if (tool->ret == open_err)
			set_expand(data, "?", "1");
		lexer_len = skip_node(data->words, lexer_len);
		ignore_all_sigs();
		handle_pipe(data, tool);
		create_and_exec_child(data, cmd, env_tab, tool);
		redirect_pipe_out(data, tool->pipe_fd);
		cmd = cmd->next;
		tool->i++;
	}
	ft_free_tab(&env_tab);
}
