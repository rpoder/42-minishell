/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:27:13 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/12 14:59:29 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tablen(char **ptr)
{
	int	i;

	if (ptr == NULL)
		return (0);
	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}
