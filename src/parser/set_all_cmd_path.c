/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:44 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 15:02:20 by mpourrey         ###   ########.fr       */
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
		global_free(data, malloc_err);
	return (path_tab);
}

static int	fill_cmd_path(t_cmd_node *cmd, char **path_tab, t_p_tool *tool)
{
	char	*tmp;

	while (path_tab[tool->i])
	{	
		tmp = ft_strsjoin(3, path_tab[tool->i], "/", cmd->cmd_tab[0]);
		if (!tmp)
			return (malloc_err);
		else if (access(tmp, F_OK & X_OK) == 0)
		{
			cmd->path = tmp;
			return (no_err);
		}
		free(tmp);
		tool->i++;
	}
	return (no_err);
}

static int	set_cmd_path(t_cmd_node *cmd, char **path_tab, t_p_tool *tool)
{
	int	ret;

	if (is_path_to_cmd(cmd->cmd_tab[0]))
	{
		cmd->path = ft_alloc_and_fill(cmd->cmd_tab[0]);
		if (!cmd->path)
			return (malloc_err);
		return (no_err);
	}
	if (path_tab)
	{
		ret = fill_cmd_path(cmd, path_tab, tool);
		if (ret == malloc_err)
			return (malloc_err);
		if (cmd->path)
			return (no_err);
	}
	cmd->path = ft_alloc_and_fill("/");
	return (no_err);
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
			if (tool->ret != no_err)
			{
				ft_free_tab(&path_tab);
				global_free(data, malloc_err);
			}
			tmp = tmp->next;
		}
	}
	ft_free_tab(&path_tab);
}
