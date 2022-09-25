/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_handle_write.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:44:30 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 15:02:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddress(unsigned long int n)
{
	int	j;

	j = write(1, "0x", 2);
	j += (ft_itoabase_uli(n, "0123456789abcdef"));
	return (j);
}

int	ft_putunint(unsigned int n, char *base)
{
	int	j;

	j = (ft_itoabase_ui(n, base));
	return (j);
}

int	ft_putint(int n)
{
	int				j;
	unsigned int	un_n;

	j = 0;
	if (n < 0)
	{
		j += write(1, "-", 1);
		un_n = (unsigned int)(n * -1);
	}
	else
		un_n = (unsigned int)n;
	j += ft_putunint(un_n, "0123456789");
	return (j);
}

int	ft_putstr(char *str)
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
		j = write(1, str, len);
	}
	return (j);
}

int	ft_putchar(char c)
{
	int	j;

	j = write(1, &c, 1);
	return (j);
}
