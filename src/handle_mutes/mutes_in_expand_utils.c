/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutes_in_expand_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:13:09 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/28 00:46:43 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mute_tool	*clear_mute_tool(t_mute_tool *tool)
{
	tool->i = 0;
	tool->len = 0;
	tool->quote = '0';
	return (tool);
}

t_mute_tool	*init_mute_tool()
{
	t_mute_tool	*mute_tool;

	mute_tool = malloc(sizeof(t_mute_tool));
	if(!mute_tool)
		return (NULL);
	mute_tool->i = 0;
	mute_tool->len = 0;
	mute_tool->quote = '0';
	return (mute_tool);
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