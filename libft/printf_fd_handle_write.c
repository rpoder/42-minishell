/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd_handle_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:44:30 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 15:02:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddress_fd(unsigned long int n, int fd)
{
	int	j;

	j = write(1, "0x", 2);
	j += (ft_itoabase_uli_fd(n, "0123456789abcdef", fd));
	return (j);
}

int	ft_putunint_fd(unsigned int n, char *base, int fd)
{
	int	j;

	j = (ft_itoabase_ui_fd(n, base, fd));
	return (j);
}

int	ft_putint_fd(int n, int fd)
{
	int				j;
	unsigned int	un_n;

	j = 0;
	if (n < 0)
	{
		j += write(fd, "-", 1);
		un_n = (unsigned int)(n * -1);
	}
	else
		un_n = (unsigned int)n;
	j += ft_putunint_fd(un_n, "0123456789", fd);
	return (j);
}
