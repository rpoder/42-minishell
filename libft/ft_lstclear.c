/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:58:06 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/10 18:40:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = NULL;
	if (lst && *lst)
	{
		while ((*lst) != NULL)
		{
			if (del)
				del((*lst)->content);
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
	*lst = NULL;
}
