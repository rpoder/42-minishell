/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:09:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/18 16:09:27 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freeptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	while (i > 0)
	{
		free(ptr[i -1]);
		i--;
	}
	free(ptr);
	ptr = NULL;
}
