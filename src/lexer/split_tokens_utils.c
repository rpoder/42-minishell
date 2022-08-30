/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:49:00 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/30 18:58:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split_tool	*init_split_tool()
{
	t_split_tool	*split_tool;

	split_tool = malloc(sizeof(t_split_tool)); //proteger
	split_tool->i = 0;
	split_tool->nb_of_tokens = 0;
	split_tool->token_start = 0;
	return (split_tool);
}

void	set_tool_for_next_token(t_split_tool *split_tool, int i)
{
	split_tool->nb_of_tokens++;	
	split_tool->token_start = i;
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
