/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:58:06 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/01 17:31:53 by ronanpoder       ###   ########.fr       */
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
