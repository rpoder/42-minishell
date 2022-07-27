/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:05:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/07/27 15:26:59 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*casted_s;

	i = ft_strlen(s);
	casted_s = (char *)s;
	while (i + 1 > 0)
	{
		if (casted_s[i] == (char)c)
			return ((&casted_s[i]));
		i--;
	}
	return (NULL);
}
