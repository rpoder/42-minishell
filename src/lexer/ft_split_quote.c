/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/15 17:28:25 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (is_split_space(str[i]))
		i = skip_space(str, i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes(str, i);
			if (str[i] == '\0')
				count++;
		}
		if (is_split_separator(str[i]))
		{
			count++;
			i = skip_separator (str, i);
			
		}
		else if (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			i++;
			if (str[i] == '\0' || is_redirection_token(str[i]))
				count++;
		}
	}
	return (count);
}

char **ft_split_quote(char *str)
{
	char	**dst;
	int		count;

	count = count_words(str);
	printf("count of words = %d\n", count);
	return (dst);
}
