/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:09:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/08 20:11:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***ptr)
{
	int		i;

	i = 0;
	if (*ptr)
	{
		while ((*ptr)[i] != NULL)
			i++;
		i--;
		while (i >= 0)
		{
			free((*ptr)[i]);
			(*ptr)[i] = NULL;
			i--;
		}
		free(*ptr);
		*ptr = NULL;
	}
}
