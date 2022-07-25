/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:44:04 by mpourrey          #+#    #+#             */
/*   Updated: 2022/07/12 22:52:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isprint(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
