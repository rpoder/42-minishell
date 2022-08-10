/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:51:14 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/10 14:09:33 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\0')
				return (1);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
				i++;
			if (str[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
