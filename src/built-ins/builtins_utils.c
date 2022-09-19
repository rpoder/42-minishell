/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:18:48 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/18 22:14:47 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_expand_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* int	is_valid_expand_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_' && key[0] != '?'
		|| (key[0] && key[0] == '?' && key[1] != '\0'))
		return (-1);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (-1);
		i++;
	}
	return (0);
} */
