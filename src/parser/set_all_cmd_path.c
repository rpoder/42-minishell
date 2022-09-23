/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:44 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 18:13:27 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_path_tab(t_data *data)
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

static int	fill_cmd_path(t_cmd_node *cmd, char **path_tab, t_p_tool *tool)
{
	char	*tmp;

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

static int	set_cmd_path(t_cmd_node *cmd, char **path_tab, t_p_tool *tool)
{
	int	ret;

	if (is_path_to_cmd(cmd->cmd_tab[0]))
	{
		cmd->path = ft_alloc_and_fill(cmd->cmd_tab[0]);
		if (!cmd->path)
			return (MALLOC_ERR);
		return (NO_ERR);
	}
	if (path_tab)
	{
		ret = fill_cmd_path(cmd, path_tab, tool);
		if (ret == MALLOC_ERR)
			return (MALLOC_ERR);
		if (cmd->path)
			return (NO_ERR);
	}
	cmd->path = ft_alloc_and_fill("/");
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
			tool->i = 0;
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
