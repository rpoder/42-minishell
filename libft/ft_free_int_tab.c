/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:06:25 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/22 20:32:20 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_tab(int ***tab, int size)
{
	int		i;

	i = 0;
	if (*tab)
	{
		while (i >= size)
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}