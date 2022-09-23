/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:47:06 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/23 15:34:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	del_unfound_expand(void *expand)
{
	if ((char *)expand)
		free((char *)expand);
}

void	del_expand(void *expand)
{
	if ((t_expand *)expand)
	{
		if (((t_expand *)expand)->key)
			free(((t_expand *)expand)->key);
		if (((t_expand *)expand)->value)
			free(((t_expand *)expand)->value);
		free((t_expand *)expand);
	}
}

void	del_cmd(void *cmd)
{
	t_list	*heredoc;

	if ((t_cmd_node *)cmd)
	{
		if (((t_cmd_node *)cmd)->path)
			free(((t_cmd_node *)cmd)->path);
		if (((t_cmd_node *)cmd)->cmd_tab)
			ft_free_tab(&((t_cmd_node *)cmd)->cmd_tab);
		if (((t_cmd_node *)cmd)->fd_in >= 0)
			close(((t_cmd_node *)cmd)->fd_in);
		if (((t_cmd_node *)cmd)->fd_out >= 0)
			close(((t_cmd_node *)cmd)->fd_out);
		if (((t_cmd_node *)cmd)->heredocs)
		{
			heredoc = ((t_cmd_node *)cmd)->heredocs;
			while (heredoc)
			{
				unlink((char *)heredoc->content);
				heredoc = heredoc->next;
			}
			ft_lstclear(&((t_cmd_node *)cmd)->heredocs, &free);
		}
		free((t_cmd_node *)cmd);
	}
}
