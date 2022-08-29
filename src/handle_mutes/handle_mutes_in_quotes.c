/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutes_in_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:20:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/29 15:02:35 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mute_and_skip_inside_quotes(t_data *data, int i)
{
	if (data->prompt_line[i] == '\'')
	{
		i++;
		while (data->prompt_line[i] != '\'')
		{
			if (data->prompt_line[i] == '\"'
				|| is_redirection_operator(data->prompt_line[i]))
				data->prompt_line[i] = data->prompt_line[i] * -1;
			i++;
		}
	}
	else if (data->prompt_line[i] == '\"')
	{
		i++;
		while (data->prompt_line[i] != '\"')
		{
			if (data->prompt_line[i] == '\''
				|| is_redirection_operator(data->prompt_line[i]))
				data->prompt_line[i] = data->prompt_line[i] * -1;
			i++;
		}
	}
	i++;
	return (i);
}

void	mute_in_quotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->prompt_line[i])
	{
		if (data->prompt_line[i] == '\'' || data->prompt_line[i] == '\"')
			i = mute_and_skip_inside_quotes(data, i);
		else
			i++;
	}			
}
