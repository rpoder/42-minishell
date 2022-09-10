/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:15:54 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/10 20:20:29 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(int i)
{
	char	*nb;
	char	*heredoc;

	nb = ft_itoa(i);
	if (!nb)
		return (NULL);
	if (access("tmp/", F_OK) == 0)
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
	free(tool->heredoc_path);
	free(tool->ret);
	free(tool->lim);
	free(tool);
}

t_heredoc_tool	*init_heredoc_tool(char *lim)
{
	t_heredoc_tool	*tool;

	tool = malloc(sizeof(t_heredoc_tool));
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
