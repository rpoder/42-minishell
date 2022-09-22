/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:16:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/22 02:40:03 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	move_to_env(t_data *data, char *key_to_export)
{
	t_list	*tmp;
	t_list	*last;

	if (!data->local_expands)
		return ;
	tmp = data->local_expands;
	last = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_expand *)tmp->content)->key, key_to_export) == 0)
			break ;
		last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (last == NULL)
		data->local_expands = tmp->next;
	else
		last->next = tmp->next;
	tmp->next = NULL;
	ft_lstadd_back(&data->env, tmp);
}

char	*trim_and_alloc_value(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len] && str[len] == '=')
		len++;
	value = malloc(sizeof(char) * (ft_strlen(str + len) + 1));
	if (!value)
		return (NULL);
	j = 0;
	i = len;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

char	*trim_and_alloc_key(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;

	ret = NO_ERR;
	i = 1;
	key = NULL;
	value = NULL;
	while (args[i])
	{
		key = trim_and_alloc_key(args[i]);
		// proteger
		value = trim_and_alloc_value(args[i]);
		// proteger
		if (!is_valid_expand_key(key))
		{
			ft_printf_fd("export:\'%s\': not a valid identifier\n", 2, key);
			ret = PARSING_ERR;
		}
		else if (value && value[0])
		{
			if (set_on(&data->env, key, value) == false)
			{
				printf("key =%s | value =%s\n", key, value);
				add_expand(data, &data->env, key, value);
			}
		}
		else
		{
			move_to_env(data, args[i]);
			if (key != NULL)
				free(key);
			if (value != NULL)
				free(value);
		}
		i++;
	}
	if (ret == NO_ERR)
		set_expand(data, "?", "0");
	else
		set_expand(data, "?", "1");
	return (ret);
}
