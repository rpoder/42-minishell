/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:52:44 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/16 17:32:08 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	alloc_and_fill_unexisting_expand(t_cmd_node *cmd, int j, char *word)
{
	int	i;
	int	start;

	i = 0;
	while (word[i] && word[i] < 0)
		i++;
	if (ft_strlen(word) - i > 0)
	{
		cmd->cmd_tab[j] = malloc(sizeof(char) * ((ft_strlen(word) - i) + 1));
		if (!cmd->cmd_tab[j])
			return (MALLOC_ERR);
		start = 0;
		while (word[i] != '\0')
		{
			cmd->cmd_tab[j][start] = word[i];
			start++;
			i++;
		}
		cmd->cmd_tab[j][start] = '\0';
	}
	return (NO_ERR);
}

static int	alloc_and_fill_cmd_tab_word(t_cmd_node *cmd, int j, char *word)
{
	int	ret;

	if (word[0] > 0 || word[0] * -1 != '*')
	{
		cmd->cmd_tab[j] = ft_alloc_and_fill(unmute_word(word));
		if (!cmd->cmd_tab[j])
			return (MALLOC_ERR);
	}
	else if (word[0] < 0 && word[0] * -1 == '*')
	{
		ret = alloc_and_fill_unexisting_expand(cmd, j, word);
		if (ret == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (NO_ERR);
}

int	set_cmd_tab(char **words, int i, t_cmd_node *cmd)
{
	int	j;
	int	ret;

	cmd->cmd_tab = malloc(sizeof(char *) * (cmd_tab_len(words, i) + 1));
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
