/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:47:33 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/17 12:06:08 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	*set_quotes(char c, t_quotes *quotes)
{
	if (c == '\"')
		quotes->dbl_quote = !quotes->dbl_quote;
	if (c == '\'')
		quotes->sgl_quote = !quotes->sgl_quote;
	return(quotes);
}

void	add_expand(t_list **alst, char *key, char *value)
{
	t_list		*lst;
	t_expand	*content;

	content = malloc(sizeof(t_expand));
	if (!content)
		global_free();
	content->key = key;
	content->value = value;
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}


