/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:26:25 by mpourrey          #+#    #+#             */
/*   Updated: 2022/03/24 18:36:36 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_dst(char *s1, char *s2, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	}
	if (s2 != NULL)
	{
		while (s2[j])
		{
			dst[i] = s2[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;

	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst = ft_fill_dst(s1, s2, dst);
	return (dst);
}
