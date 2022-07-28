/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 15:37:35 by ronanpoder       ###   ########.fr       */
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
	while (dollar_value[k])
	{
		printf("j = %d\n", j);
		data->prompt_line[j] = dollar_value[k];
		j++;
		k++;
	}
}

void	fill_interpreted_arg(t_data *data, char *src, char *dst, int len)
{
	int	i;
	int	j;
	t_quotes	quotes;
	int		tmp;

	quotes = init_quotes();
	i = 0;
	j = 0;
	while (src[i])
	{
		printf("str[%d] = %c et ", i, src[i]);
		printf("%d\n", j);
		quotes = set_quotes(src[i],quotes);
		if (src[i] == '$' && is_to_interpret(src, i, quotes.sgl_quote, quotes.dbl_quote))
		{
			fill_with_dollar_value(data, src, i, j);
			tmp = dollar_value_len(data, src, i + 1);
			printf("dollar_value_len = %d\n", tmp);
			if (tmp > 0)
				i = i + dollar_key_len(src, i + 1);
			j = j + tmp;
		}
		else
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
}

char *metachar_interpreter(t_data *data, char *src)
{
	char	*dst;
	int		dst_len;

	printf("src = %s\n", src);
	if (!has_metachar(src))
		return (src);
	dst_len = interpreted_dst_len(data, src);
	data->prompt_line = malloc(sizeof(char) * (dst_len + 1));
	if (!data->prompt_line)
		return (NULL);
	fill_interpreted_arg(data, src, dst, dst_len);


	printf("data->prompt_line = |%s|\n", dst);
	printf("len_final data->prompt_line = |%d|\n", ft_strlen(data->prompt_line));
	return (dst);
}

