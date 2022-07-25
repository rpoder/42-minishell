/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_issorted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:40:27 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/10 18:40:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tab_issorted(long int *tab, int len)
{
	int	i;
	int	j;

	i = 0;
	j = i + 1;
	while (j < len)
	{
		if (tab[i] > tab[j])
			return (1);
		i++;
		j++;
	}
	return (0);
}
