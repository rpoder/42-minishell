/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/16 19:12:45 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_and_skip_token(char **token, char *str, int i, int token_start)
{
	
	
	
}

char	**fill_dst(char **dst, char *str)
{
	int	i;
	int	start_token;
	int	k;

	i = 0;
	token_start = 0;
	k = 0;
	while (str[i])
	{
		if (is_split_separator(str, i))
		{
			dst[k] = get_token(str, i, token_start);
			i = skip_separator(str, i);
			k++;
			token_start = i;	
		}
	}
}

static int	count_words(char *str, int count)
{
	int	i;

	i = skip_space(str, 0);
	while (str[i])
	{
		if (is_split_separator(str[i]))
		{
			i = skip_separator(str, i);
			count++;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes_token(str, i);
			if (str[i] == '\0')
				count++;
		}
		else
		{
			i++;
			if (str[i] == '\0' || is_redirection_operator(str[i]))
				count++;
		}
	}
	return (count);
}

char	**ft_split_quote(char *str)
{
	char	**dst;
	int		count;

	count = count_words(str, 0);
	dst = malloc (sizeof(char *) * (count + 1));
	//proteger
	dst = fill_dst(dst, str);

	return (dst);
}
