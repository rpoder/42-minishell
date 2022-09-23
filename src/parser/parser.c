/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 01:41:02 by rpoder           ###   ########.fr       */
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

static int	set_and_skip_cmd(t_data *data, t_cmd_node *cmd, t_p_tool *tool)
{
	tool->ret = create_heredocs(data->words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR && tool->ret != OPEN_ERR)
		return (tool->ret);
	tool->ret = check_redir_op_err(data->words, tool->i);
	if (tool->ret != NO_ERR)
		return (tool->ret);
	tool->ret = set_cmd_tab(data->words, tool->i, cmd, tool);
	if (tool->ret != NO_ERR)
		return (tool->ret);
	while (data->words[tool->i] && data->words[tool->i][0] != '|')
		tool->i++;
	return (NO_ERR);
}

static t_cmd_node	*make_and_skip_cmd(t_data *d, char **words, t_p_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = init_cmd_node();
	if (!cmd_node)
		return (NULL);
	tool->ret = set_and_skip_cmd(d, cmd_node, tool);
	if (tool->ret != NO_ERR)
		free(cmd_node);
	if (tool->ret == MALLOC_ERR)
	{
		free(tool);
		global_free(d, MALLOC_ERR);
	}
	return (cmd_node);
}

int	parser(t_data *data)
{
	t_p_tool		*tool;
	t_cmd_node		*cmd_node;

	if (is_valid_expand_declaration(data->words))
	{
		set_expand_declaration(data, data->words[0]);
		return (-1);
	}
	tool = init_p_tool();
	if (!tool)
		global_free(data, MALLOC_ERR);
	while (data->words[tool->i])
	{
		cmd_node = make_and_skip_cmd(data, data->words, tool);
		if (tool->ret != NO_ERR)
		{
			if (tool->ret == CTRL_C)
				set_expand(data, "?", "130");
			free(tool);
			return (-1);
		}
		add_node_to_cmd_lst(data, cmd_node, tool);
		if (data->words[tool->i] && data->words[tool->i][0] == '|')
		{
			if (data->words[tool->i][1])
				return (free(tool), -1);
			tool->i++;
		}
	}
	set_all_cmd_path(data, tool);
	free(tool);
	return (0);
}
