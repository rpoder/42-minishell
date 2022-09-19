/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/19 20:28:13 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_node_to_cmd_lst(t_data *d, t_cmd_node *cmd_node, t_p_tool *tool)
{
	t_list			*lst;

	lst = ft_lstnew(cmd_node);
	if (!lst)
	{
		free(tool);
		del_cmd(cmd_node);
		global_free(d, MALLOC_ERR);
	}
	ft_lstadd_back(&d->cmds, lst);
}

static int	set_and_skip_cmd(char **words, t_cmd_node *cmd, t_p_tool *tool)
{
	tool->ret = set_redirection(words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR && tool->ret != OPEN_ERR)
		return (tool->ret);
	tool->ret = set_cmd_tab(words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR)
		return (tool->ret);
	while (words[tool->i] && words[tool->i][0] != '|')
		tool->i++;
	return (NO_ERR);
}

static t_cmd_node	*make_and_skip_cmd(t_data *d, char **words, t_p_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = init_cmd_node();
	if (!cmd_node)
		return (NULL);
	tool->ret = set_and_skip_cmd(words, cmd_node, tool);
	if (tool->ret != NO_ERR)
	{
		free(cmd_node);
		free(tool);
	}
	if (tool->ret == MALLOC_ERR)
		global_free(d, MALLOC_ERR);
	else if (tool->ret == PARSING_ERR)
		global_free(d, PARSING_ERR);
	else if (tool->ret == ERR_NOT_DEFINED)
		global_free(d, ERR_NOT_DEFINED);
	return (cmd_node);
}

int	parser(t_data *data)
{
	t_p_tool		*tool;
	t_cmd_node		*cmd_node;

	tool = init_p_tool();
	if (!tool)
		global_free(data, MALLOC_ERR);
	while (data->words[tool->i])
	{
		cmd_node = make_and_skip_cmd(data, data->words, tool);
		add_node_to_cmd_lst(data, cmd_node, tool);
		if (data->words[tool->i] && data->words[tool->i][0] == '|')
		{
			if (data->words[tool->i][1])
			{
				free(tool);
				global_free(data, PARSING_ERR);
			}
			tool->i++;
		}
	}
	free(tool);
	set_all_cmd_path(data);
	return (0);
}
