/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:12:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/05 16:16:45 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_str_neg(long int n, char *str, size_t len)
{
	size_t	reste;

	str[len + 1] = '\0';
	str[0] = '-';
	while (len >= 1)
	{
		reste = n % 10;
		str[len] = reste + 48;
		len--;
		n = n / 10;
	}
	return (str);
}

static char	*ft_fill_str_pos(size_t n, char *str, size_t len)
{
	size_t	reste;

	str[len] = '\0';
	len--;
	while (len + 1 > 0)
	{
		reste = n % 10;
		str[len] = reste + 48;
		len--;
		n = n / 10;
	}
	return (str);
}

static size_t	ft_intlen(size_t n)
{
	size_t	i;

	i = 0;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	size_t		nb;
	char		*str;
	size_t		len;

	nb = (size_t) n;
	if (n >= 0)
	{
		len = ft_intlen(nb);
		str = (char *) ft_calloc(len + 1, sizeof (char));
		if (str == NULL)
			return (NULL);
		ft_fill_str_pos(nb, str, len);
	}
	if (n < 0)
	{
		nb = -nb;
		len = ft_intlen(nb);
		str = (char *) ft_calloc(len + 2, sizeof (char));
		if (str == NULL)
			return (NULL);
		ft_fill_str_neg(nb, str, len);
	}
	return (str);
}
