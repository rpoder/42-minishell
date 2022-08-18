/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/18 15:50:01 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//trim dst

static char	**trim_dst(char **dst)
{
	int		i;

	i = 0;
	while(dst[i] != NULL)
	{
		dst[i] = token_trim(dst[i]);
	//	printf("token_trim = %s\n", dst[i]);
		i++;
	}
	return (dst);
}

static char	**fill_dst(char **dst, char *str, t_split_data *data)
{
	data->i = skip_space(str, 0);
	while (str[data->i])
	{
		if (is_separator(str[data->i]))
		{
			dst[data->nb_of_tokens] = get_and_skip_token(str, data);
			set_data_for_next_token(data, data->i);
		}
		else if (str[data->i] == '\'' || str[data->i] == '\"')
		{
			data->i = skip_quotes_token(str, data->i);
			dst[data->nb_of_tokens] = get_token_if_end_of_str(str, data);
		}
		else
		{
			data->i++;
			if (is_redirection_operator(str[data->i])) //token_til_redir_op
			{
				dst[data->nb_of_tokens] = get_token(str, data->i, data->token_start);
				set_data_for_next_token(data, data->i);
			}
			dst[data->nb_of_tokens] = get_token_if_end_of_str(str, data);
		}
	}
	return(dst);
}

static int	count_words(char *str, int count)
{
	int	i;

	i = skip_space(str, 0);
	while (str[i])
	{
		if (is_separator(str[i]))
		{
			i = skip_separator(str, i);
			count++;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes_token(str, i);
			if (str[i] == '\0')
				count++;
		}
		else
		{
			i++;
			if (str[i] == '\0' || is_redirection_operator(str[i]))
				count++;
		}
	}
	return (count);
}

char	**split_tokens(char *str)
{
	char			**dst;
	int				count;
	t_split_data	*split_data;

	split_data = init_split_data();
	count = count_words(str, 0);
	dst = malloc (sizeof(char *) * (count + 1));
	//proteger
	dst[count] = NULL;
	dst = fill_dst(dst, str, split_data); //proteger
	dst = trim_dst(dst); //proteger
	return (dst);
}
