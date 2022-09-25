/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 20:31:12 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_one_child(t_data *d, int **wait_ret, int j, t_exec_tool *tool)
{
	wait_ret[j] = malloc(sizeof(int));
	if (!wait_ret[j])
	{
		ft_free_int_tab(&wait_ret, tool->i);
		free_exec_tool(&tool);
		global_free(d, malloc_err);
	}
	if (waitpid(tool->fork_ret[j], wait_ret[j], 0) < 0)
	{
		ft_free_int_tab(&wait_ret, tool->i);
		free_exec_tool(&tool);
		global_free(d, waitpid_err);
	}
}

static void	set_last_exit_status(t_data *d, int **wait_ret, int j,
	t_exec_tool *tool)
{
	int		*sig;
	char	*tmp;

	sig = wait_ret[j];
	if (WIFEXITED(*sig))
	{
		tmp = ft_itoa(WEXITSTATUS(*sig));
		if (!tmp)
		{
			ft_free_int_tab(&wait_ret, tool->i);
			free_exec_tool(&tool);
			global_free(d, malloc_err);
		}
		if (set_malloced_value_expand(d, "?", tmp) == malloc_err)
		{
			free(tmp);
			ft_free_int_tab(&wait_ret, tool->i);
			free_exec_tool(&tool);
			global_free(d, malloc_err);
		}
	}
	else if (WIFSIGNALED(*sig))
		set_expand(d, "?", "130");
}

static void	wait_all_children(t_data *data, t_exec_tool *tool)
{
	int		j;
	int		**wait_ret;

	wait_ret = malloc(sizeof(int *) * tool->i);
	if (!wait_ret)
	{
		free_exec_tool(&tool);
		global_free(data, malloc_err);
	}
	ft_clear_int_tab(&wait_ret, tool->i);
	j = 0;
	while (j < tool->i)
	{
		wait_one_child(data, wait_ret, j, tool);
		set_last_exit_status(data, wait_ret, j, tool);
		j++;
	}
	ft_free_int_tab(&wait_ret, tool->i);
}

void	executer(t_data *data)
{
	t_exec_tool	*tool;
	int			lexer_len;

	lexer_len = 0;
	tool = init_exec_tool(data->cmds);
	if (!tool)
		global_free(data, malloc_err);
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
			global_free(data, dup_err);
		}
	}
	free_exec_tool(&tool);
}
