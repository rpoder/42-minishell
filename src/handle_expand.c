/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:53:13 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 13:06:11 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ATTENTION si rien dans value

void	add_expand(t_list **alst, char *key, char *value) //recoit str allouees
{
	t_list		*lst;
	t_expand	*content;

	printf("add expand\n");
	content = malloc(sizeof(t_expand));
	if (!content)
		global_free();
	content->key = key;
	content->value = get_muted_expand_value(value);
	free(value);
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}