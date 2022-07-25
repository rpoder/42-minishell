/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_isdbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:36:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/10 18:37:02 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tab_isdbl(long int *tab, int len)
{
	int	i;
	int	j;

	if (tab == 0 || len == 0)
		return (0);
	i = 0;
	while (i <= len)
	{
		j = i + 1;
		while (j < len)
		{
			if (tab[i] == tab[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
