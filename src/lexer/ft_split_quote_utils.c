/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:08:52 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/15 17:31:13 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_separator(char *str, int i)
{
	if (is_redirection_token(str[i]))
	{
		i = skip_redirection_token(str, i);
		if (is_split_space(str[i]))
			i = skip_space(str, i);
	}
	else if (is_split_space(str[i]))
		i = skip_space(str, i);
	return (i);
}

int	skip_redirection_token(char *str, int i)
{
//	printf("pour str[%d] = %c", i, str[i]);
 	if (str[i] == '>' && str[i + 1] == '>')
		i = i + 2;
	else if (str[i] == '<' && str[i + 1] == '<')
		i = i + 2;
	else 
		i++;
//	printf(" , return i = %d\n", i);
	return (i);
}

int	skip_quotes(char *str, int i)
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
	i++;
	while (str[i] == ' ' || (str[i] > 0 && str[i] <= 31) || str[i] == 127)
		i++;
	return (i);
}

int	is_redirection_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_split_space(char c)
{
	if (c == ' ' || (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}

int	is_split_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}
