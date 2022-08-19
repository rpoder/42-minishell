/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutes_in_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:43 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 15:13:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	

static char	get_muted_char_inside_quotes(char *value, int i, char quote)
{
	char	c;
	
	if (quote == '\"')
	{
		if(value[i] == '\'' || is_separator(value[i]))
			c = value[i] * -1;
		else
			c = value[i];
	}
	else if (quote == '\'')
	{
		if(value[i] == '\"' || is_separator(value[i]))
			c = value[i] * -1;
		else
			c = value[i];
		return (c);
	}
	return (c);
}

static void	fill_muted_expand_dst(char *value, char *dst)
{
	t_mute_data	*data;
	
	data = init_mute_data();
	while (value[data->i])
	{
		if (value[data->i] == '\'' || value[data->i] == '\"')
		{
			data->quote = value[data->i];
			data->i++;
			while(value[data->i] != data->quote)
			{
				dst[data->j] = get_muted_char_inside_quotes(value, data->i, data->quote);
				data->j++;
				data->i = skip_if_space(value, data->i);
			}
			data->i++;	
		}	
		else if (value[data->i])
		{
			dst[data->j] = value[data->i];
			data->j++;
			data->i = skip_if_space(value, data->i);
		}
	}
	dst[data->j] = '\0';
}

char	*get_muted_expand_value(char *value)
{
	char	*dst;

	dst = (malloc(sizeof(char) * 10)); //TEST
	//get len
	//dst = malloc(sizeof(char) * (len + 1));
	fill_muted_expand_dst(value, dst);
	
	return (dst);
}

