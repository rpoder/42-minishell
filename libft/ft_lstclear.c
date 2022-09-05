/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:58:06 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/05 14:12:18 by rpoder           ###   ########.fr       */
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
			{
				del((*lst)->content);
				(*lst)->content = NULL;
			}
			tmp = (*lst)->next;
			free(*lst);
			*lst = tmp;
		}
	}
	*lst = NULL;
}
