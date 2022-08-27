/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:53:13 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/28 00:44:26 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_expand(t_data *data, t_list **alst, char *key, char *value)
{
	t_list		*lst;
	t_expand	*content;

	content = malloc(sizeof(t_expand));
	if (!content)
		global_free(data);
	content->key = key;
	content->value = value;
	content->value = get_muted_expand_value(value); //marche pas
	free(value);
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}