/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:32:04 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/10 15:33:55 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*dst && i < dstsize)
	{
		i++;
		dst++;
	}
	if (i == dstsize)
		return (i + ft_strlen(src));
	j = 0;
	while (src[j])
	{
		if (j < (dstsize - 1 - i))
		{
			*dst = src[j];
			dst++;
		}
		j++;
	}
	*dst = '\0';
	return (i + j);
}
