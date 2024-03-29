/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:19:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 16:23:26 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
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
