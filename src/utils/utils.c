/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:19:17 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/29 15:19:42 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>'
		|| (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}

int	is_redirection_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}
