/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/21 22:49:21 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_node_to_cmd_lst(t_data *d, t_cmd_node *cmd_node, t_p_tool *tool)
{
	t_list			*lst;

	lst = ft_lstnew((void *)cmd_node);
	if (!lst)
	{
		free(tool);
		del_cmd(cmd_node);
		global_free(d, MALLOC_ERR);
	}
	ft_lstadd_back(&d->cmds, lst);
}

static int	set_and_skip_cmd(t_data *d, char **words, t_cmd_node *cmd, t_p_tool *tool)
{
	tool->ret = create_and_fill_heredocs(words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR && tool->ret != OPEN_ERR)
		return (tool->ret);
	tool->ret = set_cmd_tab(words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR)
		return (tool->ret);
	tool->ret = set_expand_declarations(d, words, tool->i, cmd, tool);
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
	tool->ret = set_and_skip_cmd(d, words, cmd_node, tool);
	if (tool->ret != NO_ERR)
		free(cmd_node);
	if (tool->ret == MALLOC_ERR)
	{
		free(tool);
		global_free(d, MALLOC_ERR);
	}
	if (tool->ret == PARSING_ERR)
	{
		free(tool);
		global_free(d, PARSING_ERR);
	}
	if (tool->ret == ERR_NOT_DEFINED)
	{
		free(tool);
		global_free(d, ERR_NOT_DEFINED);
	}
	if (tool->ret == FORK_ERR)
	{
		free(tool);
		global_free(d, FORK_ERR);
	}
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
	set_all_cmd_path(data, tool);
	free(tool);
	return (0);
}
