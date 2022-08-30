/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/27 14:49:47 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand_data	*init_expand_data(void)
{
	t_expand_data	*expand_data;

	expand_data = malloc(sizeof(t_expand_data)); //proteger
	expand_data->i = 0;
	expand_data->len = 0;
	expand_data->quotes = init_quotes; //protéger
	return (expand_data);
}

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
