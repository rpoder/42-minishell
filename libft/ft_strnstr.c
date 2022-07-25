/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:36:24 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/05 22:52:16 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < n)
		{	
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
			k++;
		}
		i++;
	}
	return (NULL);
}
