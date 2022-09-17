/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/16 11:52:54 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_expand_tool(t_expand_tool *expand_tool)
{
	free(expand_tool->quotes);
	free(expand_tool);
}

void	clear_expand_tool(t_expand_tool *expand_tool)
{
	expand_tool->i = 0;
	expand_tool->len = 0;
	clear_quotes(expand_tool->quotes);
}

t_expand_tool	*init_expand_tool(void)
{
	t_expand_tool	*expand_tool;

	expand_tool = malloc(sizeof(t_expand_tool));
	if (!expand_tool)
		return (NULL);
	expand_tool->i = 0;
	expand_tool->len = 0;
	expand_tool->quotes = malloc(sizeof(t_quotes));
	if (!expand_tool->quotes)
	{
		free(expand_tool);
		return (NULL);
	}
	clear_expand_tool(expand_tool);
	return (expand_tool);
}
