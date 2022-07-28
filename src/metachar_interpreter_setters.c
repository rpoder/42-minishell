/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter_setters.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:47:33 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 14:50:07 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	set_quotes(char c, t_quotes quotes)
{
	if (c == '\"')
		quotes.dbl_quote = !quotes.dbl_quote;
	if (c == '\'')
		quotes.sgl_quote = !quotes.sgl_quote;
	return(quotes);
}
