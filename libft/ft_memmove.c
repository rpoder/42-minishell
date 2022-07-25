/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:55:23 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/10 19:41:45 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*casted_dst;
	const char	*casted_src;
	size_t		i;

	if (src == NULL && dst == NULL)
		return (NULL);
	casted_dst = (char *)dst;
	casted_src = (const char *)src;
	if (dst > src)
	{
		i = n - 1;
		while (i + 1 > 0)
		{
			casted_dst[i] = casted_src[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
