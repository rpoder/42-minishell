/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 04:16:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_one_child(t_data *data, int **waitpid_ret, int j, t_exec_tool *tool)
{
	waitpid_ret[j] = malloc(sizeof(int));
	if (!waitpid_ret[j])
	{
		ft_free_int_tab(&waitpid_ret, tool->i);
		free_exec_tool(&tool);
		global_free(data, MALLOC_ERR);
	}
	if (waitpid(tool->fork_ret[j], waitpid_ret[j], 0) < 0)
	{
		ft_free_int_tab(&waitpid_ret, tool->i);
		free_exec_tool(&tool);
		global_free(data, WAITPID_ERR);
	}
}

static void	set_last_exit_status(t_data *data, int **waitpid_ret, int j, t_exec_tool *tool)
{
	int		*sig;
	char	*tmp;

	sig = waitpid_ret[j];
	if (WIFEXITED(*sig))
	{
		tmp = ft_itoa(WEXITSTATUS(*sig));
		if (!tmp)
		{
			ft_free_int_tab(&waitpid_ret, tool->i);
			free_exec_tool(&tool);
			global_free(data, MALLOC_ERR);
		}
		set_malloced_expand(data, "?", tmp);
	}
	else if (WIFSIGNALED(*sig))
		set_expand(data, "?", "130");
}

void	wait_all_children(t_data *data, t_exec_tool *tool)
{
	int		j;
	int		**waitpid_ret;

	waitpid_ret = malloc(sizeof(int *) * tool->i);
	if (!waitpid_ret)
	{
			free_exec_tool(&tool);
			global_free(data, MALLOC_ERR);
	}
	ft_clear_int_tab(&waitpid_ret, tool->i);
	j = 0;
	while (j < tool->i)
	{
		wait_one_child(data, waitpid_ret, j, tool);
		set_last_exit_status(data, waitpid_ret, j, tool);
		j++;
	}
	ft_free_int_tab(&waitpid_ret, tool->i);
}

void	executer(t_data *data)
{
	t_exec_tool	*tool;
	int			j;
	int			lexer_len;

	lexer_len = 0;
	tool = init_exec_tool(data->cmds);
	if (!tool)
		global_free(data, MALLOC_ERR);
	if (ft_lstlen(data->cmds) == 1
		&& is_builtin(((t_cmd_node *)data->cmds->content)->cmd_tab[0]) >= 0)
			exec_no_child_builtin(data, data->cmds, tool);
	else
	{
		exec_children(data, data->cmds, tool);
		wait_all_children(data, tool);
		if (dup2(tool->fd_stdin, 0) < 0)
		{
			free_exec_tool(&tool);
			global_free(data, DUP_ERR);
		}
	}
	free_exec_tool(&tool);
}
