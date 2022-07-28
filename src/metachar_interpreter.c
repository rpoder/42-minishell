/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:02:08 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 15:11:02 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_with_dollar_value(char *dst, int i, char *dollar_value)
{
	int	j;

	j = 0;
	while (dollar_value[j])
	{
		dst[i] = dollar_value[j];
		i++;
		j++;
	}
}

void	fill_interpreted_arg(t_data *data, char *src, char *dst, int len)
{
	int	i;
	int	j;
	t_quotes	quotes;
	char	*dollar_value;
	char	*dollar_key;
	int		tmp;

	quotes = init_quotes();
	i = 0;
	j = 0;
	while (i < len)
	{
		quotes = set_quotes(src[i],quotes);
		if (src[i] == '$' && is_to_interpret(src, i, quotes.sgl_quote, quotes.dbl_quote))
		{
			dollar_key = find_dollar_key(src, i + 1);
			dollar_value = find_dollar_value(data->shellvars, dollar_key);
			free(dollar_key);
			fill_with_dollar_value(dst, j, dollar_value);

			tmp = dollar_value_len(data, src, i + 1);
			if (tmp > 0)
				i = i + dollar_key_len(src, i + 1);
			else
				j++;
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
	dst = malloc(sizeof(char) * (dst_len + 1));
	if (!dst)
		return (NULL);
	fill_interpreted_arg(data, src, dst, dst_len);


	printf("DST = |%s|\n", dst);
	printf("len_final_dst = |%d|\n", ft_strlen(dst));
	return (dst);
}

