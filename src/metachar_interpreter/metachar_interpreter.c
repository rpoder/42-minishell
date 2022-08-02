/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/02 15:40:43 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prompt_line_len(char *str)
{
	int			i;
	t_quotes	quotes;
	int			len;
	int			tmp;

	quotes = init_quotes();
	i = 0;
	len = 0;
	while(str[i])
	{
		quotes = set_quotes(str[i], quotes);
		if (str[i] == '$' && is_to_interpret(str, i, quotes.sgl_quote, quotes.dbl_quote))
		{
			tmp = dollar_value_len(str, i + 1);
			if (tmp > 0)
			{
				i = i + dollar_key_len(str, i + 1);
				len = len + tmp;
			}
			else
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

static void	fill_with_dollar_value(char *src, int i, int j)
{
	char	*dollar_value;
	char	*dollar_key;
	int		k;

	k = 0;
	dollar_key = get_dollar_key(src, i + 1);
	dollar_value = get_dollar_value(dollar_key);
	free(dollar_key);
	if(dollar_value)
	{
		while (dollar_value[k])
		{
			data->prompt_line[j] = dollar_value[k];
			j++;
			k++;
		}
	}
}

static void	fill_prompt_line(char *src)
{
	int			i;
	int			j;
	t_quotes	quotes;

	quotes = init_quotes();
	i = 0;
	j = 0;
	while (src[i])
	{
		quotes = set_quotes(src[i], quotes);
		if (src[i] == '$' && is_to_interpret(src, i, quotes.sgl_quote, quotes.dbl_quote))
		{
			fill_with_dollar_value(src, i, j);
			j = j + dollar_value_len(src, i + 1);
			i = i + dollar_key_len(src, i + 1);
		}
		else
		{
			data->prompt_line[j] = src[i];
			j++;
		}
		i++;
	}
	data->prompt_line[j] = '\0';
}

char *metachar_interpreter(char *src)
{
	int		dst_len;

	if (!has_metachar(src))
	{
		data->prompt_line = alloc_and_fill(src);
		return (0);
	}
	dst_len = prompt_line_len(src);
	data->prompt_line = malloc(sizeof(char) * (dst_len + 1));
	// if (!data->prompt_line)
	// 	global_free();
	fill_prompt_line(src);
	printf("prompt_line %s\n", data->prompt_line);

	return (data->prompt_line);
}

