/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/22 20:32:55 by mpourrey         ###   ########.fr       */
=======
/*   Updated: 2022/09/22 20:28:35 by rpoder           ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_children(t_data *data, t_exec_tool *tool)
{
	printf("wait all children\n");
	int	j;
	int	**waitpid_ret;
	int	*sig;

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
		waitpid_ret[j] = malloc(sizeof(int));
		if (!waitpid_ret[j])
		{
			ft_free_int_tab(&waitpid_ret, tool->i);
			free_exec_tool(&tool);
			global_free(data, MALLOC_ERR);
		}
	//	waitpid(tool->fork_ret[j], waitpid_ret[j], 0);
		if (waitpid(tool->fork_ret[j], waitpid_ret[j], 0) < 0)
		{
			ft_free_int_tab(&waitpid_ret, tool->i);
			free_exec_tool(&tool);
			global_free(data, WAITPID_ERR);
		}
<<<<<<< HEAD
		set_expand(data, "?", ft_itoa(WEXITSTATUS(*waitpid_ret[j]))); //A FREE
=======
		sig = waitpid_ret[j];
		if (WIFEXITED(*sig))
		{
			// ft_printf_fd("WITH EXIT", 2);
			// ft_printf_fd("%d\n\n", WEXITSTATUS(*sig));
			set_expand(data, "?", ft_itoa(WEXITSTATUS(*waitpid_ret[j])));
		}
		else if (WIFSIGNALED(*sig))
		{
			// ft_printf_fd("WITH SIG", 2);
			set_expand(data, "?", "130");
		}
		// ft_printf_fd("proces[%d] = %d\n", 2, j , get_expand_value(data, "?"));
>>>>>>> master
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
