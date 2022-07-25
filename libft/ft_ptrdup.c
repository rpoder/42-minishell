/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:43:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/05/15 18:30:54 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ptrdup(char **ptr)
{
	int		ptr_len;
	char	**dst;
	int		i;

	i = 0;
	if (ptr == NULL)
		return (NULL);
	ptr_len = ft_ptrlen(ptr);
	dst = (char **)malloc((ptr_len + 1) * sizeof(char *));
	if (dst == NULL)
		return (NULL);
	while (i < ptr_len)
	{
		dst[i] = ft_strdup(ptr[i]);
		if (dst[i] == NULL)
			return (NULL);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
