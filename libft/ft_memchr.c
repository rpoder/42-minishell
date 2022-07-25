/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:22:34 by mpourrey          #+#    #+#             */
/*   Updated: 2021/11/26 17:54:24 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*casted_s;
	unsigned char			casted_c;
	size_t					i;

	casted_s = (const unsigned char *)s;
	casted_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (casted_s[i] == casted_c)
			return ((void *)&casted_s[i]);
		i++;
	}
	return (0);
}
