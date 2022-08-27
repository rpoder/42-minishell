/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutes_in_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:14:43 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/28 00:51:30 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

static int	muted_expand_value_len(char *src, t_mute_tool *tool)
{
	int			len;

	len = 0;
	while (src[tool->i])
	{
		if (src[tool->i] == '\'' || src[tool->i] == '\"')
		{
			tool->quote = src[tool->i];
			tool->i++;
			while (src[tool->i] != tool->quote)
			{
				len++;
				tool->i = skip_if_space(src, tool->i);
			}
			tool->i++;
		}	
		else if (src[tool->i])
		{
			len++;
			tool->i = skip_if_space(src, tool->i);
		}
	}
	return (len);
}

static char	get_muted_char_inside_quotes(char *src, int i, char quote)
{
	char	c;

	if (quote == '\"')
	{
		if (src[i] == '\'' || is_separator(src[i]))
			c = src[i] * -1;
		else
			c = src[i];
	}
	else if (quote == '\'')
	{
		if (src[i] == '\"' || is_separator(src[i]))
			c = src[i] * -1;
		else
			c = src[i];
		return (c);
	}
	return (c);
}

static void	fill_muted_expand_dst(char *src, char *dst, t_mute_tool *tool)
{
	while (src[tool->i])
	{
		if (src[tool->i] == '\'' || src[tool->i] == '\"')
		{
			tool->quote = src[tool->i];
			tool->i++;
			while (src[tool->i] != tool->quote)
			{
				dst[tool->len] = get_muted_char_inside_quotes(src,
						tool->i, tool->quote);
				tool->len++;
				tool->i = skip_if_space(src, tool->i);
			}
			tool->i++;
		}	
		else if (src[tool->i])
		{
			dst[tool->len] = src[tool->i];
			tool->len++;
			tool->i = skip_if_space(src, tool->i);
		}
	}
	dst[tool->len] = '\0';
}

char	*get_muted_expand_value(char *src)
{
	char		*dst;
	int			len;
	t_mute_tool	*mute_tool;

	mute_tool = init_mute_tool();
	if (!mute_tool)
		return (NULL);
	len = muted_expand_value_len(src, mute_tool);
	dst = (malloc(sizeof(char) * len + 1));
	if (!dst)
	{
		free(mute_tool);
		return (NULL);
	}
	mute_tool = clear_mute_tool(mute_tool);
	fill_muted_expand_dst(src, dst, mute_tool);
	free(mute_tool);
	printf("dst = %s\n", dst);
	return (dst);
}
