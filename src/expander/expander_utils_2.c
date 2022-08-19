/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/18 16:56:21 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_key_len(char *str, int i)
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

int	expand_value_len(char *str, int i)
{
	int		expand_value_len;
	char	*expand_key;
	char	*expand_value;

	expand_key = get_expand_key(str, i);
	expand_value = get_expand_value(expand_key);
	expand_value_len = ft_strlen(expand_value);
	free(expand_key);
	return (expand_value_len);
}
