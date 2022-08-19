/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:49:00 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/18 16:49:35 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_trim_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(is_space(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	while(str[j] != '\0')
		j++;
	j--;
	while(is_space(str[j]))
		j--;
	if (str[j] == '\'' || str[j] == '\"')
		j--;
	return (j - i + 1);
}

char	*token_trim(char *str)
{
	char	*dst;
	int		i;
	int		j;
	int		len;
	
	len = token_trim_len(str);
//	printf("len = %d\n", len);
 	dst = malloc(sizeof(char) * (len + 1));
	i = 0;
	while(is_space(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	len = len + i;
	j = 0;
	while (i < len)
	{
		dst[j] = str[i];
		j++;
		i++;
	}
	free (str); 
	return (dst);
}

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