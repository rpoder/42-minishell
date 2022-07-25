/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:14:14 by mpourrey          #+#    #+#             */
/*   Updated: 2022/05/06 20:45:24 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (str == NULL)
		return (1);
	len = ft_strlen(str);
	write(fd, str, len);
	return (0);
}
