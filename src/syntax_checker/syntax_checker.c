/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:51:14 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/15 18:41:40 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirection_token_checker(char *str, int i)
{
	int	j;

	j = 0;
	if (str[i] == '|')
	{
		i++;
		if (str[i] == '|')
			return (-1);
	}
	if (str[i] == '>')
	{
		if (r_chevron_checker(str, i));
		
		i++;
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
				return (-1);
		}
		if (str[i] == '<')
			return (-1);
	}
	if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				return (-1);
		}
		if (str[i] == '>')
			return (-1);
	}
	return (0);
}
int	syntax_checker(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\0')
			{
				printf("syntax error\n")
				return (1);
			}
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
				i++;
			if (str[i] == '\0')
				return (1);
		}
		else if (is_redirection_token(str[i]))
		{
			if (redirection_token_checker(str, i) != 0)
			{		
				/*dernier token printed*/
				while (is_redirection_token(str[i]))
					i++;
				printf("syntax error near unexpected token `%c'\n", str[i - 1]); /////////printf_fd ?
				return (1);
			}
		}
		i++;
	}
	return (0);
}
