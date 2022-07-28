/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 16:37:48 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_with_dollar_value(t_data *data, char *src, int i, int j)
{
	char	*dollar_value;
	char	*dollar_key;
	int		k;

	k = 0;
	dollar_key = find_dollar_key(src, i + 1);
	dollar_value = find_dollar_value(data->shellvars, dollar_key);
	free(dollar_key);
	if(dollar_value)
	{
		while (dollar_value[k])
		{
			printf("j = %d\n", j);
			data->prompt_line[j] = dollar_value[k];
			j++;
			k++;
		}
	}
}

void	fill_interpreted_arg(t_data *data, char *src, int len)
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
			fill_with_dollar_value(data, src, i, j);
			j = j + dollar_value_len(data, src, i + 1);
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

char *metachar_interpreter(t_data *data, char *src)
{
	int		dst_len;

	printf("src = %s\n", src);
	if (!has_metachar(src))
		return (src);
	dst_len = interpreted_dst_len(data, src);
	data->prompt_line = malloc(sizeof(char) * (dst_len + 1));
	if (!data->prompt_line)
		return (NULL);
	fill_interpreted_arg(data, src, dst_len);

	printf("---------data->prompt_line = |%s|\n", data->prompt_line);
	printf("len_final data->prompt_line = |%d|\n", ft_strlen(data->prompt_line));
	return (data->prompt_line);
}

