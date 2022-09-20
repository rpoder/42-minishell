/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expand_declarations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:41:19 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/20 18:48:46 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_value_declaration(char *word, char *value)
{
	int		key_len;
	int		i;
	
	key_len = 0;
	while (word[key_len] != '=')
		key_len++;
	value = malloc(sizeof(char) * (ft_strlen(word) - key_len + 1));
	if (!value)
		return (MALLOC_ERR);
	i = 0;
	key_len++;
	while (word[key_len])
	{
		value[i] = word[key_len];
		key_len++;
		i++;
	}
	value[i] = '\0'; 
	return (NO_ERR);
}

static int	set_key_declaration(char *word, char *key)
{
	int		len;
	
	len = 0;
	while (word[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (MALLOC_ERR);
	len = 0;
	while (word[len] != '=')
	{
		key[len] = word[len];
		len++;
	}
	key[len] = '\0'; 
	return (NO_ERR);
}

int	set_expand_declarations(t_data *data, char **word, int i, t_cmd_node *cmd, t_p_tool *tool)
{
	char	*key;
	char	*value;

	while (word[i] && is_expand_declaration(word[i]))
	{
		tool->ret = set_key_declaration(word[i], key);
		if (tool->ret != NO_ERR)
			return (tool->ret);
		tool->ret = set_value_declaration(word[i], value);
		if (tool->ret != NO_ERR)
		{
			free(key);
			return (tool->ret);
		}
	//	add_expand(data, &cmd->expand_declarations, key, value);
		i++;
	}
	return (NO_ERR);
	
}