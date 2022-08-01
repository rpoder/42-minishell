/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt_line_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:43:27 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/01 17:09:09 by ronanpoder       ###   ########.fr       */
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

int	dollar_value_len(char *str, int i)
{
	int		dollar_value_len;
	char	*dollar_key;
	char	*dollar_value;

	dollar_key = get_dollar_key(str, i);
	dollar_value = get_dollar_value(dollar_key);
	dollar_value_len = ft_strlen(dollar_value);
	free(dollar_key);
	return (dollar_value_len);
}
