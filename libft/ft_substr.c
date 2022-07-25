/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 23:39:22 by mpourrey          #+#    #+#             */
/*   Updated: 2022/05/13 19:11:40 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dstlen(char *s, int start, int len)
{
	int	i;

	i = 0;
	while (s[start] && i < len)
	{
		i++;
		start++;
	}	
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*dst;
	int		i;
	int		dst_len;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	dst_len = ft_dstlen(s, start, len);
	dst = (char *)malloc((dst_len + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < dst_len && s[start])
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}
