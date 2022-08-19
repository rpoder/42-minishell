/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutes_in_expand_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:13:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/19 15:14:15 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mute_data	*init_mute_data()
{
	t_mute_data	*mute_data;

	mute_data = malloc(sizeof(t_mute_data)); //proteger
	mute_data->i = 0;
	mute_data->j = 0;
	mute_data->quote = '0';
	return (mute_data);
}

int	skip_if_space(char *value, int i) 
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