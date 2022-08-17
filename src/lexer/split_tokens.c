/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:45:16 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 18:37:23 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*init_split_vars()
{
	t_vars	*split_vars;

	split_vars = malloc(sizeof(t_vars)); //proteger
	split_vars->count = 0;
	split_vars->token_start = 0;
	return (split_vars);
}

void	set_vars_for_next_token(t_vars *split_vars, int i)
{
	split_vars->count++;
	split_vars->token_start = i;
}

static char	**fill_dst(char **dst, char *str, t_vars *vars)
{
	int		i;
	
	i = skip_space(str, 0);
	while (str[i])
	{
		if (is_split_separator(str[i]))
		{
			dst[vars->count] = get_separator_token(str, i, vars->token_start);
			i = skip_separator(str, i);
			set_vars_for_next_token(vars, i);	
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes_token(str, i);
			if (str[i] == '\0') //check_is_last_token
				dst[vars->count] = get_token(str, i, vars->token_start);
		}
		else
		{
			i++;
			if (str[i] == '\0') //check_is_last_token
				dst[vars->count] = get_token(str, i, vars->token_start); 
			else if (is_redirection_operator(str[i])) //token_til_redir_op
			{
				dst[vars->count] = get_token(str, i, vars->token_start);
				set_vars_for_next_token(vars, i);
			}
		}
	}
	return(dst);
}

static int	count_words(char *str, int count)
{
	int	i;

	i = skip_space(str, 0);
	while (str[i])
	{
		if (is_split_separator(str[i]))
		{
			i = skip_separator(str, i);
			count++;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			i = skip_quotes_token(str, i);
			if (str[i] == '\0')
				count++;
		}
		else
		{
			i++;
			if (str[i] == '\0' || is_redirection_operator(str[i]))
				count++;
		}
	}
	return (count);
}

char	**split_tokens(char *str)
{
	char	**dst;
	int		count;
	t_vars	*split_vars;

	split_vars = init_split_vars();
	count = count_words(str, 0);
	dst = malloc (sizeof(char *) * (count + 1));
	//proteger
	dst[count] = NULL;
	dst = fill_dst(dst, str, split_vars);

	return (dst);
}
