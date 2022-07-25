/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:44:56 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/12 19:50:32 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
		{
			if ((str[i] != '+' && str[i] != '-') || (i != 0)
				|| (str[i + 1] < 48 || str[i + 1] > 57))
				return (1);
		}
		i++;
	}
	return (0);
}
