/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/12 15:14:07 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_tab(t_data *data)
{
	char	**env_tab;

	env_tab = malloc(sizeof(char) * (ft_lstlen(data->env) +1));
	if (!env_tab)
		global_free(data, MALLOC_ERR);
	
	return (env_tab);
}

int	is_last_cmd(t_list *cmd)
{
	if (cmd->next == NULL)
		return (1);
	return (0);
}

int	is_first_cmd(t_data *data, t_list *cmd)
{
	if (data->cmds == cmd)
		return (1);
	return (0);
}
