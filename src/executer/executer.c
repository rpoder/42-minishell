/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/22 14:38:49 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_children(t_data *data, t_exec_tool *tool)
{
	int	j;
	int	**waitpid_ret;

	waitpid_ret = malloc(sizeof(int *) * tool->i);
	if (!waitpid_ret)
		return ; // proteger
	j = 0;
	while (j < tool->i)
	{
		waitpid_ret[j] = malloc(sizeof(int));
		// proteger
		if (waitpid(tool->fork_ret[j], waitpid_ret[j], 0) < 0)
		{
			free_exec_tool(&tool);
			global_free(data, WAITPID_ERR);
		}
		set_expand(data, "?", ft_itoa(WEXITSTATUS(*waitpid_ret[j])));
		// printf("ret %d = %d\n", j, WEXITSTATUS(*waitpid_ret[j]));
		j++;
	}
}

void	exec_no_child_builtin(t_data *data, t_list *cmd, t_exec_tool *tool)
{
	char	**env_tab;

	tool->ret = open_and_set_fds(data->words, 0, (t_cmd_node *)cmd->content); //proteger////////
	if (tool->ret != NO_ERR)
	{
		if (tool->ret == MALLOC_ERR)
		{
			free_exec_tool(&tool);
			global_free(data, tool->ret);
		}
		else
		{
			free_exec_tool(&tool);
			//return (-1); >> free_line_datas(data);
		}
	}
	tool->fd_stdout = dup(1);
	if (tool->fd_stdout < 0)
	{
		free_exec_tool(&tool);
		global_free(data, DUP_ERR);
	}
	env_tab = get_env_tab(data);
	if (!env_tab)
	{
		free_exec_tool(&tool);
		global_free(data, MALLOC_ERR);
	}
	chevron_redirection(data, (t_cmd_node *)cmd->content, tool);
	if (exec_builtins(data, ((t_cmd_node *)cmd->content)->cmd_tab, false) != NO_ERR)
	{
		ft_free_tab(&env_tab);
		free_exec_tool(&tool);
		global_free(data, MALLOC_ERR);
	}
	ft_free_tab(&env_tab);
	if (dup2(tool->fd_stdout, 1) < 0)
	{
		free_exec_tool(&tool);
		global_free(data, DUP_ERR);
	}
}

void	execute_cmds(t_data *data, t_list *cmd)
{
	t_exec_tool	*tool;
	int			j;
	int			lexer_len;

	lexer_len = 0;
	tool = init_exec_tool(cmd);
	if (!tool)
		global_free(data, MALLOC_ERR);
	if (ft_lstlen(cmd) == 1
		&& is_builtin(((t_cmd_node *)cmd->content)->cmd_tab[0]) >= 0)
		exec_no_child_builtin(data, cmd, tool);
	else
	{
		exec_children(data, cmd, tool);
		wait_all_children(data, tool);
		// recuperer err de l'enfant
		if (dup2(tool->fd_stdin, 0) < 0)
		{
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
	}
	free_exec_tool(&tool);
}

void	executer(t_data *data)
{
	execute_cmds(data, data->cmds);
}
