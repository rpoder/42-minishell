/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 08:16:14 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 18:36:16 by rpoder           ###   ########.fr       */
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

static void	free_export_keyvalue(char *key, char *value)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
}

int	try_export_one_arg(t_data *data, char *arg, char *key, char *value)
{
	int	ret;

	ret = NO_ERR;
	if (!is_valid_expand_key(key))
	{
		ft_printf_fd("export:\'%s\': not a valid identifier\n", 2, key);
		free_export_keyvalue(key, value);
		ret = PARSING_ERR;
	}
	else if (value && value[0])
	{
		if (set_on(&data->env, key, value) == false)
			add_expand(data, &data->env, key, value);
	}
	else
	{
		move_to_env(data, arg);
		free_export_keyvalue(key, value);
	}
	return (ret);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		ret;
	char	*key;
	char	*value;

	ret = NO_ERR;
	i = 1;
	while (args[i])
	{
		if (set_trim_alloc_keyvalue(args[i], &key, &value) != NO_ERR)
			return (MALLOC_ERR);
		ret = try_export_one_arg(data, args[i], key, value);
		i++;
	}
	if (ret == NO_ERR)
		set_expand(data, "?", "0");
	else
		set_expand(data, "?", "1");
	return (NO_ERR);
}
