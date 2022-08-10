/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:08:52 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/10 16:16:33 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_split_space(char c)
{
	if (c == ' ' || (c > 0 && c <= 31) || c == 127)
		return (1);
	return (0);
}

int	is_split_separator(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>' || (c > 0 && c <= 31) || c == 127)
	{
//		printf("c = %c\n", c);
		return (1);
	}
	return (0);
}
