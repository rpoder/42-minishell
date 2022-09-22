/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 20:23:34 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_expand_declaration(char **words)
{
	int i;

	i = 0;
	if (words[0] && !words[1])
	{
		while (words[0][i])
		{
			if (words[0][i] == '=')
				return (1);
			i++;
		}
	}
	return (0);
}

int	is_expand_declaration(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_path_to_cmd(char *word)
{
	if ((word[0] == '.' && word[1] == '/') || word[0] == '/')
		return (1);
	return (0);
}

t_p_tool	*init_p_tool(void)
{
	t_p_tool	*tool;

	tool = malloc(sizeof(t_p_tool));
	if (!tool)
		return (NULL);
	tool->i = 0;
	tool->tab_len = 0;
	tool->ret = NO_ERR;
	return (tool);
}

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->path = NULL;
	cmd_node->cmd_tab = NULL;
	cmd_node->fd_in = FD_UNDEFINED;
	cmd_node->fd_out = FD_UNDEFINED;
	cmd_node->heredocs = NULL;
	return (cmd_node);
}
