/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:40:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/05 16:30:22 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_list *cmds)
{
	int	i;
	int j;

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

static t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->path = NULL;
	cmd_node->cmd_tab = NULL;
	cmd_node->fd_in = FD_UNDEFINED;
	cmd_node->fd_out = FD_UNDEFINED;
	return (cmd_node);
}

static int	check_and_set_redirection(t_data *data, char **words, int i, t_cmd_node *cmd)
{
	int ret;

	ret = 0;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			if (!is_redirection_operator(words[i + 1][0]))
			{
				if (words[i][0] == '<' && !words[i][1] && words[i + 1])
					ret = set_fd_in(data, cmd, words[i + 1]);
				else if (words[i][0] == '<' && words[i][1] == '<' && !words[i][2] && words[i + 1])
					ret = set_fd_heredoc(data, cmd, words[i + 1]);
				else if  (words[i][0] == '>' && !words[i][1] && words[i + 1])
					ret = set_fd_out(data, cmd, words[i + 1], O_TRUNC);
				else if (words[i][0] == '>' && words[i][1] == '>' && !words[i][2] && words[i + 1])
					ret = set_fd_out(data, cmd, words[i + 1], O_APPEND);
				else
					return (-1);
				i += 2;
			}
			else
				return (-1);
		}
		if (ret != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	cmd_tab_len(char **words, int i)
{
	int	count;

	count = 0;
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	set_cmd(t_data *data, char **words, int i, t_cmd_node *cmd)
{
	int	j;
	int	len;

	j = 0;
	len = cmd_tab_len(words, i);
	cmd->cmd_tab = malloc(sizeof(char *) * (len + 1));
	if (!cmd->cmd_tab)
		return (-1);
	ft_clear_tab(&cmd->cmd_tab, len + 1);
	while (data->words[i] && !is_pipe(data->words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
				i += 2;
		else
		{
			cmd->cmd_tab[j] = alloc_and_fill(data->words[i]);
			if (!cmd->cmd_tab[j])
			{
				ft_free_ptr(&cmd->cmd_tab);
				return (-1);
			}
			i++;
			j++;
		}
	}
	return (0);
}

static int	set_and_skip_cmd_node(t_data *data, t_cmd_node *cmd, int *i)
{

	if (check_and_set_redirection(data, data->words, *i, cmd) != 0)
		return (-1);
 	if (set_cmd(data, data->words, *i, cmd) != 0)
		return (-1);
	while (data->words[*i] && data->words[*i][0] != '|')
		(*i)++;
	return (0);
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
		cmd_node = init_cmd_node();
		if (!cmd_node)
		{
			free(i);
			global_free(data, MALLOC_ERR);
		}
		if (set_and_skip_cmd_node(data, cmd_node, i) != 0)
		{
			free(cmd_node);
			free (i);
			global_free(data, MALLOC_ERR);
		}
		// verifier if valid pipe
		if (data->words[*i] && data->words[*i][0] == '|')
			(*i)++;
		lst = ft_lstnew(cmd_node);
		if (!lst)
		{
			free(i);
			del_cmd(cmd_node);
			global_free(data, MALLOC_ERR);
		}
		ft_lstadd_back(&data->cmds, lst);
	}
	free(i);
//	print_cmd(data->cmds);
	return (0);
}
