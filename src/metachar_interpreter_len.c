/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter_len.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:28:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/29 16:21:34 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_key_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && !is_separator(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	dollar_value_len(t_data *data, char *str, int i)
{
	int		dollar_value_len;
	char	*dollar_key;
	char	*dollar_value;
	int		j;

	dollar_key = malloc((dollar_key_len(str, i) + 1) * sizeof(char));
	if (!dollar_key)
		return (-1);
	j = 0;
	while (str[i + j] && !is_separator(str[i + j]))
	{
		dollar_key[j] = str[i + j];
		j++;
	}
	dollar_key[j] = '\0';
//	dollar_value = /*cherche dans notre env sinon cherche dans lst */
//	if (dollar_value == NULL)
	dollar_value = find_dollar_value(data, dollar_key);
	dollar_value_len = ft_strlen(dollar_value);
	return (dollar_value_len);
}

int	interpreted_dst_len(t_data *data, char *str)
{
	int			i;
	t_quotes	quotes;
	int			len;
	int			tmp;

	quotes = init_quotes();
	i = 0;
	len = 0;
	while(str[i++])
	{
		quotes = set_quotes(str[i], quotes);
		if (str[i] == '$' && is_to_interpret(str, i, quotes.sgl_quote, quotes.dbl_quote))
		{
			tmp = dollar_value_len(data, str, i + 1);
			if (tmp > 0)
				i = i + dollar_key_len(str, i + 1);
			else
				len++;
			len = len + tmp;
		}
		else
			len++;
	}
	printf("INTERPRETED_DST_LEN = %d\n", len);
	return (len);
}
