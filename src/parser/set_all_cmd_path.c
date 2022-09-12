/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_all_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:44 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/12 11:21:34 by ronanpoder       ###   ########.fr       */
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

int	set_cmd_path(t_cmd_node *cmd, char **path_tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strsjoin(3, path_tab[i], "/", cmd->cmd_tab[0]);
		if (!tmp)
			return (MALLOC_ERR);
		if (access(tmp, F_OK & X_OK) == 0)
		{
			cmd->path = tmp;
			return (NO_ERR);
		}
		free(tmp);
		i++;
	}
	return (NO_ERR);
}

void	set_all_cmd_path(t_data *data)
{
	char		**path_tab;
	t_list		*tmp;

	path_tab = create_path_tab(data);
	tmp = data->cmds;
	while (tmp)
	{
		if (set_cmd_path(((t_cmd_node *)tmp->content), path_tab) == MALLOC_ERR)
		{
			ft_free_tab(&path_tab);
			global_free(data, MALLOC_ERR);
		}
		tmp = tmp->next;
	}
	free(path_tab);
}
