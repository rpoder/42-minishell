/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:52:44 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/23 17:11:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_len(char *word)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] > 0 || word[i] * -1 != '*')
			len++;
		i++;
	}
	return (len);
}

static int	cmd_tab_len(char **words, int i)
{
	int	count;

	count = 0;
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i += 2;
		else if (i == 0 && is_expand_declaration(words[i]))
		{
			while (words[i] && is_expand_declaration(words[i]))
				i++;
		}
		else if (words[i][0] < 0 && words[i][0] * -1 == '*')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count + 1);
}

static int	alloc_and_fill_arg(t_cmd_node *cmd, int j, char *word)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (arg_len(word) == 0)
		return (NO_ERR);
	cmd->cmd_tab[j] = malloc(sizeof(char) * arg_len(word) + 1);
	if (!cmd->cmd_tab[j])
		return (MALLOC_ERR);
	while (word[i])
	{		
		if (word[i] < 0 && word[i] * -1 == '*')
			i++;
		else
		{
			cmd->cmd_tab[j][k] = unmute_char(word[i]);
			i++;
			k++;
		}
	}
	cmd->cmd_tab[j][k] = '\0';
	return (NO_ERR);
}

int	set_cmd_tab(char **words, int i, t_cmd_node *cmd, t_p_tool *tool)
{
	tool->tab_len = 0;
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
			tool->ret = alloc_and_fill_arg(cmd, tool->tab_len, words[i]);
			if (tool->ret == MALLOC_ERR)
				return (tool->ret);
			i++;
			if (cmd->cmd_tab[tool->tab_len] != NULL)
				tool->tab_len++;
		}
	}
	return (tool->ret);
}
