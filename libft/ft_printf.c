/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:09:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 15:02:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_arg(char c, va_list ap)
{
	int	j;

	j = 0;
	if (c == 'c')
		j = (ft_putchar((char)va_arg(ap, int)));
	if (c == 'd' || c == 'i')
		j = (ft_putint(va_arg(ap, int)));
	if (c == 'u')
		j = (ft_putunint(va_arg(ap, unsigned int), "0123456789"));
	if (c == 'x')
		j = (ft_putunint(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		j = (ft_putunint(va_arg(ap, unsigned int), "0123456789ABcdEF"));
	if (c == 's')
		j = (ft_putstr(va_arg(ap, char *)));
	if (c == 'p')
		j = (ft_putaddress(va_arg(ap, unsigned long int)));
	if (c == '%')
		j = (ft_putchar('%'));
	return (j);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		j;

	va_start(ap, s);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			j += (ft_parse_arg(s[i + 1], ap));
			i++;
		}
		else
			j += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (j);
}
