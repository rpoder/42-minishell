/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:23:42 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 18:23:44 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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