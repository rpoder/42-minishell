/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:24:29 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/10 19:40:56 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*casted_dst;
	const char	*casted_src;

	if (src == NULL && dst == NULL)
		return (NULL);
	casted_dst = (char *)dst;
	casted_src = (char *)src;
	i = 0;
	while (i < n)
	{
		casted_dst[i] = casted_src[i];
		i++;
	}
	return (dst);
}
