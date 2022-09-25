/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 16:30:37 by mpourrey         ###   ########.fr       */
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
		global_free(d, malloc_err);
	}
	ft_lstadd_back(&d->cmds, lst);
}

static int	set_and_skip_cmd(t_data *data, t_cmd_node *cmd, t_p_tool *tool)
{
	tool->ret = create_heredocs(data->words, tool->i, cmd, tool);
	if (tool->ret != no_err && tool->ret != open_err)
		return (tool->ret);
	tool->ret = check_redir_op_err(data->words, tool->i);
	if (tool->ret != no_err)
	{
		set_expand(data, "?", "2");
		return (tool->ret);
	}
	tool->ret = set_cmd_tab(data->words, tool->i, cmd, tool);
	if (tool->ret != no_err)
		return (tool->ret);
	while (data->words[tool->i] && data->words[tool->i][0] != '|')
		tool->i++;
	return (no_err);
}

static t_cmd_node	*make_and_skip_cmd(t_data *d, char **words, t_p_tool *tool)
{
	t_cmd_node	*cmd_node;

	cmd_node = init_cmd_node();
	if (!cmd_node)
		return (NULL);
	tool->ret = set_and_skip_cmd(d, cmd_node, tool);
	if (tool->ret == malloc_err)
	{
		free(cmd_node);
		free(tool);
		global_free(d, malloc_err);
	}
	return (cmd_node);
}

static int	set_all_cmd_nodes(t_data *data, t_p_tool *tool)
{
	t_cmd_node		*cmd_node;

	while (data->words[tool->i])
	{
		cmd_node = make_and_skip_cmd(data, data->words, tool);
		if (tool->ret != no_err)
		{
			if (tool->ret == ctrl_c)
				set_expand(data, "?", "130");
		}
		add_node_to_cmd_lst(data, cmd_node, tool);
		if (tool->ret != no_err)
			return (-1);
		if (data->words[tool->i] && data->words[tool->i][0] == '|')
		{
			if (data->words[tool->i][1] || !data->words[tool->i + 1])
			{
				set_expand(data, "?", "2");
				return (-1);
			}
			tool->i++;
		}
	}
	return (0);
}

int	parser(t_data *data)
{
	t_p_tool		*tool;

	if (is_valid_expand_declaration(data->words))
	{
		set_expand_declaration(data, data->words[0]);
		return (-1);
	}
	tool = init_p_tool();
	if (!tool)
		global_free(data, malloc_err);
	if (set_all_cmd_nodes(data, tool) != 0)
	{
		free(tool);
		return (-1);
	}	
	set_all_cmd_path(data, tool);
	free (tool);
	return (0);
}
