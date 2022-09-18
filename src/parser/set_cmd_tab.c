/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:52:44 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/18 20:28:51 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_tab_word_len(char *word)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
//	printf("word = %s\n", word);
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
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	alloc_and_fill_cmd_tab_word(t_cmd_node *cmd, int j, char *word)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	cmd->cmd_tab[j] = malloc(sizeof(char) * cmd_tab_word_len(word) + 1);
	if (!cmd->cmd_tab[j])
		return (MALLOC_ERR);
	while (word[i])
	{
		if (word[i] < 0 && word[i] * -1 == '*')
			i++;
		else
		{
			if (word[i] < 0)
				cmd->cmd_tab[j][k] = word[i] * -1;
			else
				cmd->cmd_tab[j][k] = word[i];
			i++;
			k++;
		}
	}
	cmd->cmd_tab[j][k] = '\0';
	return (NO_ERR);
}


int	set_cmd_tab(char **words, int i, t_cmd_node *cmd)
{
	int	j;
	int	ret;

	cmd->cmd_tab = malloc(sizeof(char *) * (cmd_tab_len(words, i) + 1)); ////
//	printf("len of cmd_tab = %d\n", (cmd_tab_len(words, i) + 1));
	if (!cmd->cmd_tab)
		return (MALLOC_ERR);
	ft_clear_tab(&cmd->cmd_tab, cmd_tab_len(words, i) + 1);
	j = 0;
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
				i += 2;
		else
		{
			ret = alloc_and_fill_cmd_tab_word(cmd, j, words[i]);
			if (ret == MALLOC_ERR)
				return (MALLOC_ERR);
			i++;
			if (cmd->cmd_tab[j] != NULL)
				j++;
		}
	}
	return (NO_ERR);
}
