/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:32:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/27 20:18:17 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_sign(int n, int fd)
{
	if (n < 0)
	{
		write (fd, "-", 1);
		return (-1);
	}
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned long	nb;

	nb = (unsigned long)n * (unsigned long)(ft_is_sign(n, fd));
	if (nb <= 9)
	{
		c = nb + 48;
		write(fd, &c, 1);
	}
	if (nb > 9)
	{
		ft_putnbr_fd (nb / 10, fd);
		ft_putnbr_fd (nb % 10, fd);
	}
}
