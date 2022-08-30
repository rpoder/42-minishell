/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:00:06 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/30 19:05:23 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*TEST*/
void	test_lexer(char **tokens)
{
	int	i;

	printf("\n");
	i = 0;
	while(tokens[i] != NULL)
	{
		printf("token[%d] = |%s|\n", i, tokens[i]);
		i++;
	}
}

void	lexer(t_data *data)
{	
	split_tokens(data);
/*	if (!data->tokens)
 	{
		printf("split_token failed\n");
		global_free(data);
	} */
	test_lexer(data->tokens);
}
