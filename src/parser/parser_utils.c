/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/16 17:31:27 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ambiguous_redirection(char *expand)
{
	char	*unmute_expand;
	int		i;

	unmute_expand = malloc(sizeof(char *) * (strlen(expand) + 1));
	i = 0;
	unmute_expand[i] = '$';
	i++;
	while (expand[i])
	{
		unmute_expand[i] = expand[i] * -1;
		i++;
	}
	ft_printf_fd("minishell: %s : ambiguous redirect\n", 2, unmute_expand);
}

char	*unmute_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] < 0 && str[i] * -1 == '*')
		return (str);
	while (str[i])
	{
		if (str[i] < 0)
			str[i] = str[i] * -1;
		i++;
	}
	return (str);
}

t_cmd_node	*init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->path = NULL;
	cmd_node->cmd_tab = NULL;
	cmd_node->fd_in = FD_UNDEFINED;
	cmd_node->fd_out = FD_UNDEFINED;
	cmd_node->heredocs = NULL;
	return (cmd_node);
}

int	cmd_tab_len(char **words, int i)
{
	int	count;
	int	j;

	count = 0;
	while (words[i] && !is_pipe(words[i][0]))
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i += 2;
		else
		{
			j = 0;
			if (words[i][j] && words[i][j] < 0 & words[i][j] * -1 == '*')
			{
				while (words[i][j] && words[i][j] < 0)
					j++;
			}
			if (words[i][j])
				count++;
			i++;
		}
	}
	return (count);
}
