/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/14 16:38:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_pipe(t_data *data)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		global_free(data, MALLOC_ERR);

	return(pipe_fd);
}

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
