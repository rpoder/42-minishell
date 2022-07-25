/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:18:52 by mpourrey          #+#    #+#             */
/*   Updated: 2022/03/24 18:31:56 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dst;

	if (str == NULL || n == 0)
		return (NULL);
	dst = malloc((n + 1) * sizeof(char));
	i = 0;
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
