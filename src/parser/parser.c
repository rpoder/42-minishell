/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/18 01:30:13 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_node	*create_and_skip_cmd(t_data *data, char **words, int *i)
{
	t_cmd_node	*cmd_node;
	int			ret;

	cmd_node = init_cmd_node();
	if (!cmd_node)
		return (NULL);
	ret = set_and_skip_cmd_node(words, cmd_node, i);
	if (ret != NO_ERR)
	{
		free(cmd_node);
		free(i);
	}
	if (ret == MALLOC_ERR)
		global_free(data, MALLOC_ERR);
	else if (ret == PARSING_ERR)
		global_free(data, PARSING_ERR);
	else if (ret == ERR_NOT_DEFINED)
		global_free(data, ERR_NOT_DEFINED);
	return (cmd_node);
}

int	parser(t_data *data)
{
	int			*i;
	t_cmd_node	*cmd_node;
	t_list		*lst;

	i = malloc(sizeof(int));
	if (!i)
		global_free(data, MALLOC_ERR);
	*i = 0;
	while (data->words[*i])
	{
		cmd_node = create_and_skip_cmd(data, data->words, i);
		lst = ft_lstnew(cmd_node);
		if (!lst)
		{
			free(i);
			del_cmd(cmd_node);
			global_free(data, MALLOC_ERR);
		}
		ft_lstadd_back(&data->cmds, lst);
		if (data->words[*i] && data->words[*i][0] == '|')
		{
			if (data->words[*i][1])
			{
				free(i);
				global_free(data, MALLOC_ERR);
			}
			(*i)++;
		}
	}
	free(i);
	set_all_cmd_path(data);
	return (0);
}
