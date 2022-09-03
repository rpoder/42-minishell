/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/03 17:47:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd_node	*init_cmd_node(void)
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

static void	set_and_skip_redirection(t_data *data, char **words, int *i, t_cmd_node *cmd)
{
	int	j;

	j = 0;
 	if (words[*i][j] == '<' && !words[*i][j + 1])
		set_fd_in(data, cmd, words[*i + 1]);
 	else if (words[*i][j] == '<' && words[*i][j + 1] == '<' && !words[*i][j + 2])
		set_fd_heredoc(data, cmd, words[*i + 1]);
	else if (words[*i][j] == '>' && !words[*i][j + 1])
		set_fd_out(data, cmd, words[*i + 1], O_TRUNC);
	else if (words[*i][j] == '>' && words[*i][j + 1] == '>' && !words[*i][j + 2])
		set_fd_out(data, cmd, words[*i + 1], O_APPEND);
	*i = 2;
}

static void	set_and_skip_cmd_node(t_data *data, t_cmd_node *cmd, int *i)
{
	while (data->words[*i] && data->words[*i][0] && data->words[*i][0] != '|')
	{
		 if (data->words[*i][0] == '<' || data->words[*i][0] == '>')
		 	set_and_skip_redirection(data, data->words, i, cmd);
		// else
		// 	i = set_and_skip_cmd(data, words, i, cmd);
	}
}

int	parser(t_data *data)
{
	int			*i;
	t_cmd_node	*cmd_node;
	t_list		*lst;

	i = malloc(sizeof(int));
	*i = 0;
	while (data->words[*i])
	{
		cmd_node = init_cmd_node();
		if (!cmd_node)
			global_free(data, MALLOC_ERR);
		set_and_skip_cmd_node(data, cmd_node, i);
		// lst = ft_lstnew(cmd_node);
		// if (!lst)
		// {
		// 	free(cmd_node);
		// 	global_free(data, MALLOC_ERR);
		// }
		// ft_lstadd_back(&data->cmds, lst);
		// verifier if valid pipe
	}
	return (0);
}
