/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:31:57 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/10 20:22:10 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*casted_s1;
	const unsigned char	*casted_s2;
	size_t				i;

	if (n == 0)
		return (0);
	casted_s1 = (const unsigned char *)s1;
	casted_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n - 1 && casted_s1[i] == casted_s2[i])
		i++;
	return (casted_s1[i] - casted_s2[i]);
}
