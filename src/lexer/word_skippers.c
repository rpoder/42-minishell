/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_skippers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:47:40 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/31 11:26:40 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_redirection_word(char *str, int i)
{
	if (str[i] == '<' || str[i] == '>')
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
	}
	else if (str[i] == '|')
	{
		while (str[i] && str[i] == '|')
			i++;
	}
	return (i);
}

int	skip_separator(char *str, int i)
{
	if (is_redirection_operator(str[i]))
	{
		i = skip_redirection_word(str, i);
		if (is_space(str[i]))
			i = skip_space(str, i);
	}
	else if (is_space(str[i]))
		i = skip_space(str, i);
	return (i);
}

int	skip_quotes_word(char *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"')
			i++;
		i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
		i++;
	}
	return (i);
}

int	skip_space(char *str, int i)
{
	while (str[i] == ' ' || (str[i] > 0 && str[i] <= 31) || str[i] == 127)
		i++;
	return (i);
}
