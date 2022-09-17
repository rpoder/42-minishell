/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:56:05 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/17 20:27:53 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_unfound_expand(t_data *data, char *str, int start, t_expand_tool *tool)
{
	char	*unexisting_expand_key;
	char	*to_save;
	t_list	*lst;
	
	unexisting_expand_key = get_expand_key(str + 1, start);
	if (!unexisting_expand_key)
	{
		free(tool->quotes);
		free(tool);
		global_free(data, MALLOC_ERR);
	}
	to_save = ft_strjoin("$", unexisting_expand_key);
	free(unexisting_expand_key);
	printf("to save = %s\n", to_save);
	lst = ft_lstnew(unexisting_expand_key);
	if (!lst)
	{
		free(unexisting_expand_key);
		free(tool->quotes);
		free(tool);
		global_free(data, MALLOC_ERR);
	}
	ft_lstadd_back(&data->unfound_expands, lst);
	
//	free(to_save);	
	
}

int	is_expand_suffix(char c, int j)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	if (c == '?' && j == 0)
		return (0);
	else
		return (1);
}

int	is_expand_separator(char c)
{
	if (c == ' ' || c == '$' || c == '|' || c == '\"' || c == '\''
		|| c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_limiter(char *str, int i)
{
	if (i > 0)
	{
		i--;
		while (str[i] && is_space(str[i]))
			i--;
		if (str[i] && str[i] == '<' && str[i - 1] == '<')
			return (1);
	}
	return (0);
}

int	is_expand_to_interpret(char *str, int i, t_quotes *quotes)
{
	if (!str[i + 1] || is_expand_separator(str[i + 1])
		|| is_expand_suffix(str[i + 1], 0) || is_limiter(str, i))
		return (0);
	if (quotes->dbl_quote)
		return (1);
	else if (quotes->sgl_quote)
		return (0);
	return (1);
}

int	has_expand(char *str)
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
