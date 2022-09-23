/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:15:54 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/23 14:50:19 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_path_to_heredoc_list(t_cmd_node *cmd, char *heredoc_path)
{
	t_list	*heredoc_node;
	char	*path_dup;

	if (heredoc_path)
	{
		path_dup = ft_alloc_and_fill(heredoc_path);
		if (!path_dup)
			return (MALLOC_ERR);
		heredoc_node = ft_lstnew(path_dup);
		if (!heredoc_node)
		{
			free(path_dup);
			return (MALLOC_ERR);
		}
		ft_lstadd_back(&cmd->heredocs, heredoc_node);
	}
	return (NO_ERR);
}

char	*get_heredoc_name(int i)
{
	char	*nb;
	char	*heredoc;

	nb = ft_itoa(i);
	if (!nb)
		return (NULL);
	if (access("/tmp/", F_OK) == 0)
		heredoc = ft_strjoin("/tmp/heredoc_", nb);
	else
		heredoc = ft_strjoin("heredoc_", nb);
	if (!heredoc)
	{
		free(nb);
		return (NULL);
	}
	free(nb);
	return (heredoc);
}

void	free_heredoc_tool(t_heredoc_tool *tool)
{
	if (tool->str)
		free(tool->str);
	if (tool->heredoc_path)
		free(tool->heredoc_path);
	if (tool->ret)
		free(tool->ret);
	if (tool->lim)
		free(tool->lim);
	free(tool);
}

t_heredoc_tool	*init_heredoc_tool(char *lim)
{
	t_heredoc_tool	*tool;

	// tool = malloc(sizeof(t_heredoc_tool));
	tool = NULL;
	if (!tool)
		return (NULL);
	tool->lim = ft_strjoin(lim, "\n");
	if (!tool->lim)
	{
		free(tool);
		return (NULL);
	}
	tool->str = NULL;
	tool->heredoc_path = NULL;
	tool->ret = malloc(sizeof(int));
	if (!tool->ret)
	{
		free(tool->lim);
		free(tool);
		return (NULL);
	}
	*(tool->ret) = NO_ERR;
	return (tool);
}
