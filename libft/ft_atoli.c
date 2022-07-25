/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:49:10 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/18 15:17:20 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoli(char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] == 48)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + ((long) str[i] - 48);
		i++;
	}
	return ((long)(sign * result));
}
