/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:42:27 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/14 20:40:59 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_fd(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = NO_ERR;
	if (words[i + 1] && !is_redirection_operator(words[i + 1][0]))
	{
		if (words[i][0] == '<' && !words[i][1] && words[i + 1])
			ret = set_fd_in(cmd, unmute_word(words[i + 1]));
		else if (words[i][0] == '<' && words[i][1] == '<'
			&& !words[i][2] && words[i + 1])
			ret = set_fd_heredoc(cmd, unmute_word(words[i + 1]));
		else if (words[i][0] == '>' && !words[i][1] && words[i + 1])
			ret = set_fd_out(cmd, unmute_word(words[i + 1]), O_TRUNC);
		else if (words[i][0] == '>' && words[i][1] == '>' &&
			!words[i][2] && words[i + 1])
			ret = set_fd_out(cmd, unmute_word(words[i + 1]), O_APPEND);
		else
			return (PARSING_ERR);
		if (ret != NO_ERR)
			return (ret);
	}
	else
		return (PARSING_ERR);
	return (NO_ERR);
}

static int	check_and_set_redirection(char **words, int i, t_cmd_node *cmd)
{
	int	ret;

	ret = NO_ERR;
	while (words[i] && words[i][0] != '|')
	{
		if (words[i][0] == '<' || words[i][0] == '>')
		{
			ret = set_fd(words, i, cmd);
			if (ret != NO_ERR)
				return (ret);
			i += 2;
		}
		else
			i++;
	}
	return (ret);
}

static int	set_cmd(char **words, int i, t_cmd_node *cmd)
{
	int	j;

	j = 0;
	cmd->cmd_tab = malloc(sizeof(char *) * (cmd_tab_len(words, i) + 1));
	if (!cmd->cmd_tab)
		return (MALLOC_ERR);
	ft_clear_tab(&cmd->cmd_tab, cmd_tab_len(words, i) + 1);
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
				i += 2;
		else
		{
			cmd->cmd_tab[j] = ft_alloc_and_fill(words[i]);
			if (!cmd->cmd_tab[j])
			{
				ft_free_tab(&cmd->cmd_tab);
				return (MALLOC_ERR);
			}
			i++;
			j++;
		}
	}
	return (NO_ERR);
}

int	set_and_skip_cmd_node(char **words, t_cmd_node *cmd, int *i)
{
	int	ret;

	ret = check_and_set_redirection(words, *i, cmd);
	if (ret != NO_ERR)
		return (ret);
	ret = set_cmd(words, *i, cmd); ////mettre ret a jour
	if (ret != NO_ERR)
		return (ret);
	while (words[*i] && words[*i][0] != '|')
		(*i)++;
	return (NO_ERR);
}
