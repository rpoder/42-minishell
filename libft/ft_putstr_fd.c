/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:14:14 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/31 13:28:55 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	j;
	int	len;

	if (str == NULL)
		j = write(1, "(null)", 6);
	else
	{
		len = 0;
		while (str[len] != '\0')
			len++;
		j = write(fd, str, len);
	}
	return (j);
}
