/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:51:14 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/31 11:31:52 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quotes(char *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"' && str[i])
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
	}
	return (i);
}

static int	redirection_word_checker(char *str, int i)
{
	if (str[i] == '|')
	{
		if (str[i - 1] && str[i - 1] == '|')
			return (1);
	}
	if (str[i] == '>')
	{
		if ((str[i - 1] && str[i - 1] == '>' && str[i - 2] && str[i - 2] == '>')
			|| (str[i - 1] && str[i - 1] == '<'))
			return (1);
	}
	if (str[i] == '<')
	{
		if ((str[i - 1] && str[i - 1] == '<' && str[i - 2] && str[i - 2] == '<')
			|| (str[i - 1] && str[i - 1] == '>'))
			return (1);
	}
	return (0);
}

int	syntax_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes(str, i);
			if (str[i] == '\0')
			{
				ft_putstr_fd("syntax error : missing closed quote\n", 2);
				return (1);
			}
		}
		else if (is_redirection_operator(str[i]))
		{
			if (redirection_word_checker(str, i) != 0)
			{
				ft_printf("syntax error near unexpected word `%c'\n", str[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
