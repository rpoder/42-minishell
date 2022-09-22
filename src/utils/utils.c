/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:19:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 16:30:40 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_node(char **words, int len)
{
	while (words[len] && words[len][0] != '|')
		len++;
	if (words[len])
		len++;
	return (len);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_word_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>'
		|| (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}

int	is_redirection_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}
