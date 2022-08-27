/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:49:00 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 17:08:12 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split_data	*init_split_data()
{
	t_split_data	*split_data;

	split_data = malloc(sizeof(t_data)); //proteger
	split_data->i = 0;
	split_data->nb_of_tokens = 0;
	split_data->token_start = 0;
	return (split_data);
}

void	set_data_for_next_token(t_split_data *split_data, int i)
{
	split_data->nb_of_tokens++;	
	split_data->token_start = i;
}

int	redirection_token_len(char *str, int i)
{
	int	len;
	
	if ((str[i] == '<' && str[i + 1] == '<') || 
		(str[i] == '>' && str[i + 1] == '>'))
		len = 2;
	else
		len = 1;
	return (len);		
}
