/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:44 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/20 19:17:20 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_path_tab(t_data *data)
{
	char	*env_path;
	char	**path_tab;

	env_path = get_expand_value(data, "PATH");
	if (!env_path)
		return (NULL);
	path_tab = ft_split(env_path, ':');
	if (!path_tab)
		global_free(data, MALLOC_ERR);
	return (path_tab);
}

int	set_cmd_path(t_cmd_node *cmd, char **path_tab, t_p_tool *tool)
{
	char	*tmp;

	if (is_path_to_cmd(cmd->cmd_tab[0]))
	{
		cmd->path = ft_alloc_and_fill(cmd->cmd_tab[0]);
		if (!cmd->path)
			return (MALLOC_ERR);
		return (NO_ERR);
	}	
	tool->i = 0;
	while (path_tab[tool->i])
	{
		tmp = ft_strsjoin(3, path_tab[tool->i], "/", cmd->cmd_tab[0]);
		if (!tmp)
			return (MALLOC_ERR);
		else if (access(tmp, F_OK & X_OK) == 0)
		{
			cmd->path = tmp;
			return (NO_ERR);
		}
		free(tmp);
		tool->i++;
	}
	return (NO_ERR);
}

void	set_all_cmd_path(t_data *data, t_p_tool *tool)
{
	char		**path_tab;
	t_list		*tmp;

	path_tab = create_path_tab(data);
	tmp = data->cmds;
	while (tmp)
	{
		if (!((t_cmd_node *)tmp->content)->cmd_tab[0])
			tmp = tmp->next;
		else
		{
			tool->ret = set_cmd_path(((t_cmd_node *)tmp->content),
					path_tab, tool);
			if (tool->ret != NO_ERR)
			{
				ft_free_tab(&path_tab);
				global_free(data, MALLOC_ERR);
			}
			tmp = tmp->next;
		}
	}
	ft_free_tab(&path_tab);
}
