/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:43:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/12 14:59:02 by ronanpoder       ###   ########.fr       */
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
	ptr_len = ft_tablen(ptr);
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
