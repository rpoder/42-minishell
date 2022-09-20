/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/20 19:29:11 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	unmute_char(char c)
{
	if (c < 0)
		c = c * -1;
	return (c);
}

int	is_expand_declaration(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_path_to_cmd(char *word)
{
	if ((word[0] == '.' && word[1] == '/') || word[0] == '/')
		return (1);
	return (0);
}

t_p_tool	*init_p_tool(void)
{
	t_p_tool	*tool;

	tool = malloc(sizeof(t_p_tool));
	if (!tool)
		return (NULL);
	tool->i = 0;
	tool->tab_len = 0;
	tool->ret = NO_ERR;
	return (tool);
}

int	unmute_word_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
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
	cmd_node->expand_declarations = NULL;
	return (cmd_node);
}
