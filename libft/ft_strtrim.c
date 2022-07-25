/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:55:23 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/27 22:42:19 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char *set, char c)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

static int	ft_isstop(char *s1, int i, char *set)
{
	i = i + 1;
	while (s1[i])
	{
		if (ft_isinset(set, s1[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_filldest(char *dest, char *s1, char *set)
{
	size_t	i;
	size_t	destcount;

	i = 0;
	destcount = 0;
	while (s1[i] && ft_isinset(set, s1[i]) == 1)
		i++;
	while (s1[i] && (ft_isinset(set, s1[i]) == 0
			|| (ft_isstop(s1, i, set) == 0)))
	{
		dest[destcount] = s1[i];
		i++;
		destcount++;
	}
	dest[destcount] = '\0';
	return (dest);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*dest;
	size_t	i;
	size_t	destcount;

	i = 0;
	destcount = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_isinset(set, s1[i]) == 1)
		i++;
	while (s1[i] && (ft_isinset(set, s1[i]) == 0
			|| (ft_isstop(s1, i, set) == 0)))
	{
		i++;
		destcount++;
	}
	dest = ft_calloc((destcount + 1), sizeof(char));
	if (dest == 0)
		return (NULL);
	dest = ft_filldest(dest, s1, set);
	return (dest);
}
