/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:53:34 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/10 18:46:56 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list *lst)
{
	int	len;

	len = 0;
	if (lst != NULL)
	{
		while (lst != NULL)
		{
			lst = lst->next;
			len++;
		}
	}
	return (len);
}
