/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:16:58 by mpourrey          #+#    #+#             */
/*   Updated: 2022/01/23 18:28:10 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_f_lstnew(t_list *lst, void *(*f)(void *))
{
	t_list	*new;

	if (f)
		new = ft_lstnew(f(lst->content));
	else
		new = ft_lstnew(lst->content);
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*last;
	t_list	*first;

	if (lst == NULL)
		return (NULL);
	last = NULL;
	while (lst)
	{
		new = ft_f_lstnew(lst, f);
		if (new == NULL)
		{
			if (last != NULL && del)
				ft_lstclear(&first, del);
			return (NULL);
		}
		if (last == NULL)
			first = new;
		else
			last->next = new;
		last = new;
		lst = lst->next;
	}
	return (first);
}
