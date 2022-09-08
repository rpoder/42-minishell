/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:42:27 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/08 20:11:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = 0;
	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{	
		if (words[i][0] == '<' && !words[i][1] && words[i + 1])
			ret = set_fd_in(cmd, words[i + 1]);
		else if (words[i][0] == '<' && words[i][1] == '<'
			&& !words[i][2] && words[i + 1])
			ret = set_fd_heredoc(cmd, words[i + 1]);
		else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
			ret = set_fd_out(cmd, words[i + 1], O_TRUNC);
		else if (words[i][0] == '>' && words[i][1] == '>' &&
			!words[i][2] && words[i + 1])
			ret = set_fd_out(cmd, words[i + 1], O_APPEND);
		else
			return (-2);
		if (ret != 0)
			return (-1);
	}
	else
		return (-2);
	return (0);
}

static int	check_and_set_redirection(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = 0;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = set_fd(words, i, cmd);
			if (ret != 0)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

static int	set_cmd(char **words, int i, t_cmd_node *cmd)
{
	int	j;

	j = 0;
	cmd->cmd_tab = malloc(sizeof(char *) * (cmd_tab_len(words, i) + 1));
	if (!cmd->cmd_tab)
		return (-1);
	ft_clear_tab(&cmd->cmd_tab, cmd_tab_len(words, i) + 1);
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
				i += 2;
		else
		{
			cmd->cmd_tab[j] = alloc_and_fill(words[i]);
			if (!cmd->cmd_tab[j])
			{
				ft_free_tab(&cmd->cmd_tab);
				return (-1);
			}
			i++;
			j++;
		}
	}
	return (0);
}

int	set_and_skip_cmd_node(char **words, t_cmd_node *cmd, int *i)
{
	int	ret;

	ret = check_and_set_redirection(words, *i, cmd);
	if (ret != 0)
		return (ret);
	ret = set_cmd(words, *i, cmd);
	if (ret != 0)
		return (ret);
	while (words[*i] && words[*i][0] != '|')
		(*i)++;
	return (0);
}
