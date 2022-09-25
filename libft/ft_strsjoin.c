/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:00:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 15:01:42 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsjoin(int nb_arg, ...)
{
	char	*new_dst;
	char	*dst;
	va_list	ap;

	va_start(ap, nb_arg);
	dst = NULL;
	while (nb_arg > 0)
	{
		new_dst = ft_strjoin(dst, va_arg(ap, char *));
		if (dst != NULL)
			free(dst);
		dst = new_dst;
		nb_arg--;
	}
	va_end(ap);
	return (dst);
}
