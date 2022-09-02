/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/02 16:59:11 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->path = NULL;
	cmd_node->exec_tab = NULL;
	cmd_node->fd_in = 0;
	cmd_node->fd_out = 0;
	return (cmd_node);
}

int	fill_and_skip_redirection(t_data *data, char **data->words, int start, t_list *cmd)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	if (data->words[i][j] == '<' && !data->words[i][j + 1])

	else if (data->words[i][j] == '<' && data->words[i][j + 1] == '<' && !data->words[i][j + 2])
	else if (data->words[i][j] == '>' && !data->words[i][j + 1])
	else if (data->words[i][j] == '>' && data->words[i][j + 1] == '>' && !data->words[i][j + 2])

	return (2);
}

int	fill_cmd_node(t_data *data, t_cmd_node *cmd, int start)
{
	int	i;

	i = start;
	while (data->words[i])
	{
		while (data->words[i][0] && data->words[i][0] != '|')
		{
			if (data->words[i][j] == '<' || data->words[i][j] == '>')
				i = fill_and_skip_redirection(data, data->words, i, cmd);
			else
				i = fill_and_skip_cmd(data, data->words, i, cmd);
		}
		i++;
	}
}

int	parser(t_data *data)
{
	int			i;
	int			j;
	t_cmd_node	*cmd_node;
	t_list		*lst;

	i = 0;
	while (data->words[i])
	{
		cmd_node = init_cmd_node();
		if (!cmd_node)
			global_free(data, MALLOC_ERR);
		i = fill_and_skip_cmd_node(data, cmd_node, i);
		lst = ft_lstnew(cmd_node);
		if (!lst)
		{
			free(cmd_node);
			global_free(data, MALLOC_ERR);
		}
		ft_lstadd_back(&data->cmds, lst);
		// verifier if valid pipe
		i++;
	}
	return (0);
}
