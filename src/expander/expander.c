/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/19 19:00:18 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expanded_line_len(char *str)
{
	int			i;
	t_quotes	*quotes;
	int			len;
	int			tmp;

	quotes = init_quotes();
	i = 0;
	len = 0;
	while(str[i])
	{
		quotes = set_quotes(str[i], quotes);
		if (str[i] == '$' && is_to_interpret(str, i, quotes->sgl_quote, quotes->dbl_quote))
		{
			tmp = expand_value_len(str, i + 1);
			if (tmp > 0)
			{
				i = i + expand_key_len(str, i + 1);
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

static void	fill_with_expand_value(char *src, int i, int j)
{
	char	*expand_value;
	char	*expand_key;
	int		k;

	k = 0;
	expand_key = get_expand_key(src, i + 1);
	expand_value = get_expand_value(expand_key);
	free(expand_key);
	if(expand_value)
	{
		while (expand_value[k])
		{
			data->expanded_line[j] = expand_value[k];
			j++;
			k++;
		}
	}
}

static void	fill_expanded_line(char *src)
{
	int			i;
	int			j;
	t_quotes	*quotes;

	quotes = init_quotes();
	i = 0;
	j = 0;
	while (src[i])
	{
		quotes = set_quotes(src[i], quotes);
		if (src[i] == '$' && is_to_interpret(src, i, quotes->sgl_quote, quotes->dbl_quote))
		{
			printf("entre\n");
			fill_with_expand_value(src, i, j);
			j = j + expand_value_len(src, i + 1);
			i = i + expand_key_len(src, i + 1);
		}
		else
		{
			data->expanded_line[j] = src[i];
			j++;
		}
		i++;
		printf("expanded_line[%d] = %c\n", j, data->expanded_line[j]);
	}
	data->expanded_line[j] = '\0';
}

void	expander(char *src)
{
	int	dst_len;

	if (!has_expand(src))
	{
		data->expanded_line = alloc_and_fill(src);
		return ;
	}
	dst_len = expanded_line_len(src);
	data->expanded_line = malloc(sizeof(char) * (dst_len + 1));
//	if (!data->expanded_line)
//		global_free();
	printf("len = %d\n", dst_len);
	fill_expanded_line(src);
}

