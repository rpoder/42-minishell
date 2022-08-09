/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/03 16:11:50 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_word(char *str, int i, t_quotes *quotes)
{
	while (!is_separator(str[i]) && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			while (str[i] != '\"')
				i++;
		}
		i++;
	}
	return (i);
}

static int	skip_sgl_quote_word(char *str, int i, t_quotes *quotes)
{
	while (quotes->sgl_quote && str[i])
	{
		if (str[i] == '\'')
		{
			if (str[i + 1] != '\'')
			{
				quotes->sgl_quote = !quotes->sgl_quote;
				while (str[i] != ' ' && str[i])
					i++;
			}
			else
				i++;
		}
		i++;
	}
	return (i);
}

static int	skip_dbl_quote_word(char *str, int i, t_quotes *quotes)
{
	while (quotes->dbl_quote && str[i])
	{
		if (str[i] == '\"')
		{
			if (str[i + 1] != '\"')
			{
				quotes->dbl_quote = !quotes->dbl_quote;
				while (str[i] != ' ' && str[i])
					i++;
			}
			else
				i++;
		}
		i++;
	}
	return (i);
}

static int	count_words(char *str)
{
	int			i;
	int			count;
	t_quotes	*quotes;

	quotes = init_quotes();
	count = 0;
	i = 0;
	while (str[i])
	{
		quotes = set_quotes(str[i], quotes);
		if (quotes->dbl_quote && str[i])
		{
			printf("word = %s | ", str + i);
			i = skip_dbl_quote_word(str, i, quotes);
			printf("last letter = %c\n", str[i]);
			count++;
		}
		else if (quotes->sgl_quote && str[i])
		{
			printf("word = %s | ", str + i);
			i = skip_sgl_quote_word(str, i, quotes);
			printf("last letter = %c\n", str[i]);
			count++;
		}
		else
		{
			printf("word = %s | ", str + i);
			i = skip_word(str, i, quotes);
			printf("last letter = %c\n", str[i]);
			count++;
		}
		i++;
	}
	return (count);
}

char **ft_split_quote(char *str)
{
	int count;

	count = count_words(str);
	printf("number of words = %d\n", count);
}
