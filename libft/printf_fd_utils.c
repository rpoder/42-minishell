/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:05:03 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/31 13:48:31 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_itoabase_ui_fd(unsigned int n, char *base, int fd)
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
	j = ft_putstr_fd(res, fd);
	free(res);
	return (j);
}

int	ft_itoabase_uli_fd(unsigned long int n, char *base, int fd)
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
	j = ft_putstr_fd(res, fd);
	free(res);
	return (j);
}
