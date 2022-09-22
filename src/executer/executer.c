/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/22 15:25:25 by rpoder           ###   ########.fr       */
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
		{
			exec_no_child_builtin(data, data->cmds, tool);
		}
	else
	{
		exec_children(data, data->cmds, tool);
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
