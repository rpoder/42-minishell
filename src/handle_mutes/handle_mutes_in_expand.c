/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutes_in_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:43 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 17:05:47 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

static int	muted_expand_value_len(char *src)
{
	t_mute_data	*data;
	int			len;
	
	data = init_mute_data();
	while (src[data->i])
	{
		if (src[data->i] == '\'' || src[data->i] == '\"')
		{
			data->quote = src[data->i];
			data->i++;
			while(src[data->i] != data->quote)
			{
				len++;
				data->i = skip_if_space(src, data->i);
			}
			data->i++;	
		}	
		else if (src[data->i])
		{
			len++;
			data->i = skip_if_space(src, data->i);
		}
	}
	free(data);
	return (len);
}

static char	get_muted_char_inside_quotes(char *src, int i, char quote)
{
	char	c;
	
	if (quote == '\"')
	{
		if(src[i] == '\'' || is_separator(src[i]))
			c = src[i] * -1;
		else
			c = src[i];
	}
	else if (quote == '\'')
	{
		if(src[i] == '\"' || is_separator(src[i]))
			c = src[i] * -1;
		else
			c = src[i];
		return (c);
	}
	return (c);
}

static void	fill_muted_expand_dst(char *src, char *dst)
{
	t_mute_data	*data;
	
	data = init_mute_data();
	while (src[data->i])
	{
		if (src[data->i] == '\'' || src[data->i] == '\"')
		{
			data->quote = src[data->i];
			data->i++;
			while(src[data->i] != data->quote)
			{
				dst[data->len] = get_muted_char_inside_quotes(src, data->i, data->quote);
				data->len++;
				data->i = skip_if_space(src, data->i);
			}
			data->i++;	
		}	
		else if (src[data->i])
		{
			dst[data->len] = src[data->i];
			data->len++;
			data->i = skip_if_space(src, data->i);
		}
	}
	dst[data->len] = '\0';
	free(data);
}

char	*get_muted_expand_value(char *src)
{
	char	*dst;
	int		len;
	
	len = muted_expand_value_len(src);
	dst = (malloc(sizeof(char) * len + 1)); //TEST
	fill_muted_expand_dst(src, dst);
	return (dst);
}

