/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:53:03 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 12:24:44 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_and_skip_token(char *str, int token_start, int i, t_list **tokens)
{
	t_list	*lst;
	char	*token;
	int		token_len;

	token_len = get_token_len();
	token = malloc(sizeof(char) * token_len); //proteger
	token = fill_token();
	lst = ft_lstnew((void *)token); //proteger
	ft_lstadd_front(tokens, lst);
}

t_list	*lst_split(char *str)
{
	int		i;
	int		token_start;
	t_list	*tokens;

	i = skip_space(str, 0);
	token_start = 0;
	tokens = NULL;
	while (str[i])
	{
		if (is_split_separator(str[i]))
		{
			i = add_and_skip_token(str, token_start, i, &tokens);
			token_start = i;
		}
	}
}