/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter_len.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:28:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/27 15:43:05 by ronanpoder       ###   ########.fr       */
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
	dollar_value = find_dollar_value(data->shellvars, dollar_key);
	printf("dollar_key = %s\n", dollar_key);
	printf("dollar_value = %s\n", dollar_value);
	dollar_value_len = ft_strlen(dollar_value);
	return (dollar_value_len);
}

int	interpreted_dst_len(t_data *data, char *str)
{
	int		i;
	bool	sgl_quote;
	bool	dbl_quote;
	int		len;

	sgl_quote = false;
	dbl_quote = false;
	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] == '\"')
			dbl_quote = !dbl_quote;
		if (str[i] == '\'')
			sgl_quote = !sgl_quote;
		if (str[i] == '$' && str[i + 1] && is_to_interpret(str, i, sgl_quote, dbl_quote))
		{
			len += dollar_value_len(data, str, i + 1);
			i += dollar_key_len(str, i + 1);
		}
		else
			len++;
		i++;
	}
	printf("total dst_len = %d\n", len);
	return (len);
}
