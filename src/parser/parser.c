/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/08 20:09:44 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_print_cmd(t_list *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds)
	{
		j = 0;
		printf("CMD %d\n", i);
		printf("path = %s\n", ((t_cmd_node *)cmds->content)->path);
		while (((t_cmd_node *)cmds->content)->cmd_tab[j])
		{
			printf("cmd_tab[%d] = %s\n", j, ((t_cmd_node *)cmds->content)->cmd_tab[j]);
			j++;
		}
		printf("fd_in = %d\n", ((t_cmd_node *)cmds->content)->fd_in);
		printf("fd_out = %d\n\n\n", ((t_cmd_node *)cmds->content)->fd_out);
		i++;
		cmds = cmds->next;
	}
}

static t_cmd_node	*create_and_skip_cmd(t_data *data, char **words, int *i)
{
	t_cmd_node	*cmd_node;
	int			ret;

	cmd_node = init_cmd_node();
	if (!cmd_node)
		return (NULL);
	ret = set_and_skip_cmd_node(words, cmd_node, i);
	if (ret == -1)
	{
		free(cmd_node);
		free(i);
		global_free(data, MALLOC_ERR);
	}
	if (ret == -2)
	{
		free(cmd_node);
		free(i);
		global_free(data, PARSING_ERR);
	}
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
		///////////////////////
		lst = ft_lstnew(cmd_node);
		if (!lst)
		{
			free(i);
			del_cmd(cmd_node);
			global_free(data, MALLOC_ERR);
		}
		ft_lstadd_back(&data->cmds, lst);

		// verifier if valid pipe
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
//	test_print_cmd(data->cmds);
	return (0);
}
