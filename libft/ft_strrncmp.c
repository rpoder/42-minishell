/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:01:18 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/30 20:40:13 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(char *s1, char *s2, int n)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (len_s1 >= 0 && len_s2 >= 0 && n > 0)
	{
		if (s1[len_s1] != s2[len_s2])
			return ((unsigned char) s1[len_s1] - (unsigned char) s2[len_s2]);
		len_s1--;
		len_s2--;
		n--;
	}
	return (0);
}
