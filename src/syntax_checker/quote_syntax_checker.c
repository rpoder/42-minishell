/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_syntax_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:30:12 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/20 15:11:08 by mpourrey         ###   ########.fr       */
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

int	quote_syntax_checker(char *str)
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
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
