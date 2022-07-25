/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:28:24 by mpourrey          #+#    #+#             */
/*   Updated: 2021/12/10 17:52:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	n;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	n = ft_strlen(s);
	dst = (char *)malloc(n + 1 * sizeof(char));
	if (dst == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
