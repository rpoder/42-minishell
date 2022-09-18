/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/18 18:22:13 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ambiguous_redirection(char *amb_redir)
{
/* 	char	*unmute_expand;
	int		i;

	unmute_expand = malloc(sizeof(char *) * (strlen(expand) + 1));
	i = 0;
	unmute_expand[i] = '$';
	i++;
	while (expand[i])
	{
		unmute_expand[i] = expand[i] * -1;
		i++;
	} */
	ft_printf_fd("minishell: %s: ambiguous redirect\n", 2, amb_redir);
}

/* char	*unmute_word(char *str)
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
} */

int		unmute_word_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	while(str[i])
	{
		if (str[i] > 0 || str[i] * -1 != '*')
			len++;
		i++;
	}
	return (len);
}

char	*unmute_word(char *str)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * unmute_word_len(str) + 1);
	if (dst == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] < 0 && str[i] * -1 == '*')
			i++;
		else
		{
			if (str[i] < 0)
				dst[j] = str[i] * -1;
			else
				dst[j] = str[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return (dst);
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
