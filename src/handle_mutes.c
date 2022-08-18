/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:43 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/18 20:37:52 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_if_space(char *value, int i) 
{
	if (is_space(value[i]))
	{
		while(is_space(value[i]))
			i++;
	}
	else
		i++;
	return (i);
}	

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

void	fill_muted_expand_dst(char *value, char *dst) //A NORMER
{
	int	i;
	int	j;
	char	quote;
	
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"') //ne pas recopier
		{
			quote = value[i];
			i++;
			while(value[i] != quote)
			{
				dst[j] = get_muted_char_inside_quotes(value, i, quote);
				j++;
				i = skip_if_space(value, i);
			}
			i++; //ne pas recopier	
		}	
		else if (value[i])
		{
			dst[j] = value[i];
			j++;
			i = skip_if_space(value, i);
		}
	}
	dst[j] = '\0';
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

static int	mute_and_skip_inside_quotes(t_data *data, int i)
{
	if (data->prompt_line[i] == '\'')
	{
		i++;
		while(data->prompt_line[i] != '\'')
		{
			if (data->prompt_line[i] == '\"' || is_redirection_operator(data->prompt_line[i]))
				data->prompt_line[i] = data->prompt_line[i] * -1;
			i++;	
		}
	}
	else if (data->prompt_line[i] == '\"')
	{
			i++;
			while(data->prompt_line[i] != '\"')
			{
				if (data->prompt_line[i] == '\'' || is_redirection_operator(data->prompt_line[i])) //separator
					data->prompt_line[i] = data->prompt_line[i] * -1;
				i++;	
			}
	}
	i++;
	return (i);
}

void	mute_non_interpretable_quotes(t_data *data)
{
	int	i;

	i = 0;
	while(data->prompt_line[i])
	{
		if(data->prompt_line[i] == '\'' || data->prompt_line[i] == '\"')
			i = mute_and_skip_inside_quotes(data, i);
		else
			i++;
	}			
}
