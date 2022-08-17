/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_getters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:42:01 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 18:24:29 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//trimer les espaces et les guillemets

char	*get_token(char *str, int i, int token_start)
{
	char	*token;
	int		len;
	int		j;
	
	j = 0;
	len = i - token_start;
	token = malloc(sizeof(char) * (len + 1)); //proteger
	while(str[token_start] != '\0' && !is_redirection_operator(str[token_start]))
	{
		token[j] = str[token_start];
		j++;
		token_start++;
	}
	token[j] = '\0';
	return (token);
}

//separer get_redir_op_token et get_token_til_space

char	*get_separator_token(char *str, int i, int token_start)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	if (is_redirection_operator(str[i]))
	{
		len = redirection_token_len(str, i);
		token = malloc(sizeof(char) * (len + 1)); //proteger
		while (j < len)
		{
			token[j] = str[i];
			j++;
		}
		token[j] = '\0';
	}
	else if (is_space(str[i]))
	{
		len = i - token_start;
		token = malloc(sizeof(char) * len + 1); //proteger
		while (token_start <= i)
		{
			token[j] = str[token_start];
			j++;
			token_start++;
		}
		token[j] = '\0';
	}	
	return (token);
}