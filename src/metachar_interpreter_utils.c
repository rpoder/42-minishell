/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_interpreter_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:32:13 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 14:20:36 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_metachar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_to_interpret(char *str, int i, int sgl_quote, int dbl_quote)
{
	if (!str[i + 1] || str[i + 1] == '$' || str[i + 1] == ' ')
		return (0);
	if (dbl_quote)
		return (1);
	else if (sgl_quote)
		return (0);
	return (1);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '$' || c == '|' || c == '\"' || c == '\'' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*find_dollar_value(t_list *shellvars, char *dollar_key)
{
	while (shellvars)
	{
		if (ft_strcmp(((t_shellvar *)shellvars->content)->key, dollar_key) == 0)
			return (((t_shellvar *)shellvars->content)->value);
		else
			shellvars = shellvars->next;
	}
	return (NULL);
}

char	*find_dollar_key(char *str, int i)
{
	int j;
	char *dollar_key;

	j = 0;
	dollar_key = malloc((dollar_key_len(str, i) + 1) * sizeof(char));
	if (!dollar_key)
		return (NULL);
	while (str[i + j] && !is_separator(str[i + j]))
	{
		dollar_key[j] = str[i + j];
		j++;
	}
	dollar_key[j] = '\0';
	return (dollar_key);
}