/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:05:03 by mpourrey          #+#    #+#             */
/*   Updated: 2022/03/24 18:33:05 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_printf(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_reslen_ui(unsigned int n, int base_len)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / (base_len);
		i++;
	}
	return (i);
}

int	ft_itoabase_ui(unsigned int n, char *base)
{
	int		base_len;
	char	*res;
	int		i;
	int		reste;
	int		j;

	if (n == 0)
		return (ft_putchar('0'));
	base_len = ft_strlen_printf(base);
	i = ft_reslen_ui(n, base_len);
	res = (char *)malloc((i + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	res[i] = '\0';
	while (i > 0)
	{	
		i--;
		reste = n % base_len;
		res[i] = base[reste];
		n = n / base_len;
	}
	j = ft_putstr(res);
	free(res);
	return (j);
}

int	ft_reslen_uli(unsigned long int n, int base_len)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / (base_len);
		i++;
	}
	return (i);
}

int	ft_itoabase_uli(unsigned long int n, char *base)
{
	int		base_len;
	char	*res;
	int		i;
	int		reste;
	int		j;

	if (n == 0)
		return (ft_putchar('0'));
	base_len = ft_strlen_printf(base);
	i = ft_reslen_uli(n, base_len);
	res = (char *)malloc((i + 1) * sizeof(char));
	if (res == NULL)
		return (0);
	res[i] = '\0';
	while (i > 0)
	{	
		i--;
		reste = n % base_len;
		res[i] = base[reste];
		n = n / base_len;
	}
	j = ft_putstr(res);
	free(res);
	return (j);
}
