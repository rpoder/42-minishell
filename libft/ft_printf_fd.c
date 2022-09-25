/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:17:46 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 15:02:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_arg_printf_fd(int fd, char c, va_list ap)
{
	int	j;

	j = 0;
	if (c == 'c')
		j = (ft_putchar_fd((char)va_arg(ap, int), fd));
	if (c == 'd' || c == 'i')
		j = (ft_putint_fd(va_arg(ap, int), fd));
	if (c == 'u')
		j = (ft_putunint_fd(va_arg(ap, unsigned int), "0123456789", fd));
	if (c == 'x')
		j = (ft_putunint_fd(va_arg(ap, unsigned int), "0123456789abcdef", fd));
	if (c == 'X')
		j = (ft_putunint_fd(va_arg(ap, unsigned int), "0123456789ABcdEF", fd));
	if (c == 's')
		j = (ft_putstr_fd(va_arg(ap, char *), fd));
	if (c == 'p')
		j = (ft_putaddress_fd(va_arg(ap, unsigned long int), fd));
	if (c == '%')
		j = (ft_putchar_fd('%', fd));
	return (j);
}

int	ft_printf_fd(const char *s, int fd, ...)
{
	va_list	ap;
	int		i;
	int		j;

	va_start(ap, fd);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			j += (ft_parse_arg_printf_fd(fd, s[i + 1], ap));
			i++;
		}
		else
			j += write(fd, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (j);
}
