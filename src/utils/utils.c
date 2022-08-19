/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:47:33 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/18 16:53:04 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	*set_quotes(char c, t_quotes *quotes)
{
	if (c == '\"')
		quotes->dbl_quote = !quotes->dbl_quote;
	if (c == '\'')
		quotes->sgl_quote = !quotes->sgl_quote;
	return(quotes);
}




