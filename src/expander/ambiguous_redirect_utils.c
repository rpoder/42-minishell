/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:33:31 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/18 19:50:49 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ambiguous_expand(char *str, int start)
{
	int	j;

	j = 0;
	start++;
	while(str[start] && (!is_expand_separator(str[start]) || is_expand_suffix(str[start], j)))
	{
		if (is_expand_suffix(str[start], j))
			return (0);
		start++;
		j++;
	}
	if (is_space(str[start]) || !str[start])
		return (1);
	return (0);
}

static int	is_redirect_expand(char *str, int start)
{
	int	i;

	i = start;
	i--;
	while (str[i] && is_space(str[i]))
		i--;
	if (str[i] && (str[i] == '>' || str[i] == '<'))
		return (1);
	return (0);
}

void	save_ambiguous_redirect(t_data *data, char *str, int start, t_expand_tool *tool)
{
	char	*unfound_expand_key;
	char	*to_save;

	if (!data->ambiguous_redirection)
	{
		if (is_redirect_expand(str, start) && is_ambiguous_expand(str, start))
		{
			unfound_expand_key = get_expand_key(str + 1, start);
			if (!unfound_expand_key)
			{
				free(tool->quotes);
				free(tool);
				global_free(data, MALLOC_ERR);
			}
			data->ambiguous_redirection = ft_strjoin("$", unfound_expand_key);
			free(unfound_expand_key);
		}
	}
}