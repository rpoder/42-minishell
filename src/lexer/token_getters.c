/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:42:01 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/30 19:53:15 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_data *data, char *src, t_split_tool *tool)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	len = tool->i - tool->token_start;
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
	{
		free(tool);
		global_free(data);
		return (token);
	}
	while (src[tool->token_start] != '\0'
		&& !is_redirection_operator(src[tool->token_start]))
	{
		token[j] = src[tool->token_start];
		j++;
		tool->token_start++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_token_if_end_of_src(t_data *data, char *src, t_split_tool *tool)
{
	char	*token;

	token = NULL;
	if (src[tool->i] == '\0')
		token = get_token(data, src, tool);
	return (token);
}

static char	*get_token_til_space(t_data *data, char *src, t_split_tool *tool)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	len = tool->i - tool->token_start;
	token = malloc(sizeof(char) * len + 1);
	if (!token)
	{
		free(tool);
		global_free(data);
		return (token);
	}
	while (tool->token_start < tool->i)
	{
		token[j] = src[tool->token_start];
		j++;
		tool->token_start++;
	}
	token[j] = '\0';
	return (token);
}

static char	*get_redir_op_token(t_data *data, char *src, t_split_tool *tool)
{
	char	*token;
	int		len;
	int		j;

	j = 0;
	len = redirection_token_len(src, tool->i);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
	{
		free(tool);
		global_free(data);
		return (token);
	}
	while (j < len)
	{
		token[j] = src[tool->i];
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_and_skip_token(t_data *data, char *src, t_split_tool *tool)
{
	char	*token;

	if (is_redirection_operator(src[tool->i]))
		token = get_redir_op_token(data, src, tool);
	else if (is_space(src[tool->i]))
		token = get_token_til_space(data, src, tool);
	tool->i = skip_separator(src, tool->i);
	return (token);
}
