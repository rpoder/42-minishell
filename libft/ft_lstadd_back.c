/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:38 by mpourrey          #+#    #+#             */
/*   Updated: 2022/05/22 19:06:28 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst != NULL && new != NULL)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
	}
}
