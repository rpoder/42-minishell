/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:42:01 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 21:53:11 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_if_end_of_str(char *str, t_split_data *data)
{
	char	*token;

	token = NULL;
	if (str[data->i] == '\0') 
			token = get_token(str, data->i, data->token_start);
	return (token);
}

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

static char	*get_token_til_space(char *str, t_split_data *data)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	len = data->i - data->token_start;
	token = malloc(sizeof(char) * len + 1); //proteger
	while (data->token_start <= data->i)
	{
		token[j] = str[data->token_start];
		j++;
		data->token_start++;
	}
	token[j] = '\0';
	return (token);
}

static char	*get_redir_op_token(char *str, t_split_data *data)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	len = redirection_token_len(str, data->i);
	token = malloc(sizeof(char) * (len + 1)); //proteger
	while (j < len)
	{
		token[j] = str[data->i];
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_and_skip_token(char *str, t_split_data *data)
{
	char	*token;
	
	if (is_redirection_operator(str[data->i]))
		token = get_redir_op_token(str, data);
	else if (is_space(str[data->i]))
		token = get_token_til_space(str, data);
	data->i = skip_separator(str, data->i);
	return (token);
}
