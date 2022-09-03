/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/03 23:43:45 by rpoder           ###   ########.fr       */
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
 	if (words[*i][j] == '<' && words[*i][j + 1])
		set_fd_in(data, cmd, words[*i + 1]);
 	else if (words[*i][j] == '<' && words[*i][j + 1] == '<' && !words[*i][j + 2])
		set_fd_heredoc(data, cmd, words[*i + 1]);
	else if (words[*i][j] == '>' && words[*i][j + 1])
		set_fd_out(data, cmd, words[*i + 1], O_TRUNC);
	else if (words[*i][j] == '>' && words[*i][j + 1] == '>' && !words[*i][j + 2])
		set_fd_out(data, cmd, words[*i + 1], O_APPEND);
	else
		global_free(data, PARSING_ERR);
	*i += 2;
}

static int	exec_tab_len(char **words, int i)
{
	int	count;

	count = 0;
	while (words[i])
	{
		while (words[i] && !is_redirection_operator(words[i][0]))
		{
			count++;
			i++;
		}
		if (words[i] && words[i][0] == '>'&& words[i][0] == '<')
			i += 2;
	}
	return (count);
}

static void	set_and_skip_cmd(t_data *data, char **words, int *i, t_cmd_node *cmd)
{
	int	j;

	j = 0;
	cmd->exec_tab = malloc(sizeof(char *) * exec_tab_len(words, *i) + 1);
	if (!cmd->exec_tab)
		global_free(data, MALLOC_ERR);
	ft_clear_tab(&cmd->exec_tab, exec_tab_len(words, *i) + 1);

	while (data->words[*i])
	{
	while (data->words[*i] && !is_redirection_operator(data->words[*i][0]))
	{
		cmd->exec_tab[j] = malloc(sizeof(char) * ft_strlen(data->words[*i]));
		if (!cmd->exec_tab[j])
		{
			ft_free_ptr(&cmd->exec_tab);
			global_free(data, MALLOC_ERR);
		}
		cmd->exec_tab[j] = alloc_and_fill(data->words[*i]);
		(*i)++;
		j++;
	}
	if (data->words[*i] && words[i][0] == '>' && words[i][0] == '<')
		(*i) += 2;
	}
	//TEST//
	// int k = 0;
	// while (cmd->exec_tab[k])
	// {
	// 	printf("exect_tab[%d] = %s\n", k, cmd->exec_tab[k]);
	// 	k++;
	// }
}

static void	set_and_skip_cmd_node(t_data *data, t_cmd_node *cmd, int *i)
{

	while (data->words[*i] && data->words[*i][0] != '|')
	{
		 if (data->words[*i][0] == '<' || data->words[*i][0] == '>')
		 	set_and_skip_redirection(data, data->words, i, cmd);
		else
			set_and_skip_cmd(data, data->words, i, cmd);
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
	printf("ok\n");

		cmd_node = init_cmd_node();
		if (!cmd_node)
			global_free(data, MALLOC_ERR);
		set_and_skip_cmd_node(data, cmd_node, i);
		// verifier if valid pipe
		if (data->words[*i] && data->words[*i][0] == '|')
			(*i)++;
		// lst = ft_lstnew(cmd_node);
		// if (!lst)
		// {
		// 	free(cmd_node);
		// 	global_free(data, MALLOC_ERR);
		// }
		// ft_lstadd_back(&data->cmds, lst);

	}
	return (0);
}
