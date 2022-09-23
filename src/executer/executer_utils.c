/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 13:59:56 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_err_or_chevron_err(t_data *data)
{
	if (ft_strcmp(get_expand_value(data, "?"), "1") == 0 ||
		ft_strcmp(get_expand_value(data, "?"), "1") == 0)
		return (1);
	return (0);
}

int	*init_pipe(t_data *data)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		global_free(data, MALLOC_ERR);
	return(pipe_fd);
}

int	is_last_cmd(t_list *cmd)
{
	if (cmd->next == NULL)
		return (1);
	return (0);
}
