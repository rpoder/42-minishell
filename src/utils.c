/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:47:33 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/01 18:02:54 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	set_quotes(char c, t_quotes quotes)
{
	if (c == '\"')
		quotes.dbl_quote = !quotes.dbl_quote;
	if (c == '\'')
		quotes.sgl_quote = !quotes.sgl_quote;
	return(quotes);
}

void	add_shellvar(t_list **alst, char *key, char *value)
{
	t_list		*lst;
	t_shellvar	*content;

	content = malloc(sizeof(t_shellvar));
	content->key = key;
	content->value = value;
	lst = ft_lstnew(content);
	ft_lstadd_back(alst, lst);
}
