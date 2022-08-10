/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/10 17:40:17 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			i++;
			while (str[i] && is_split_separator(str[i] != 1) && str[i] != '\"' && str[i] != '\'' && str[i] != ' ')
				i++;
			if (is_split_separator(str[i]) == 1 || !str[i])
			{
				count++;
				if (str[i])
					i++;
			}
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			i++;
			while (str[i] && is_split_separator(str[i] != 1) && str[i] != '\'' && str[i] != '\"' && str[i] != ' ')
				i++;
			if (is_split_separator(str[i]) == 1 || !str[i]) 
			{
				count++;
				if (str[i])
					i++;
			}
		}
		else if (str[i] && str[i] != '\"' && str[i] != '\'')
		{
			if (is_split_space(str[i]) == 1)
			{
				if (i != 0)
					count++;
				while (is_split_space(str[i]) == 1)
					i++;
			}
			else if (!str[i] || is_split_separator(str[i] == 1))
				count++;
			else
			{
				i++;
				if (!str[i])
					count++;
			}
		}
	
	}
	printf("i = %d\n", i);
	return (count);
}

char **ft_split_quote(char *str)
{
	char	**dst;
	int		count;

	count = count_words(str);
	printf("number of words = %d\n", count);
	return (dst);
}
