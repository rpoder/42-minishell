/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/31 13:57:04 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ft_lstdelone*/
void	del_one_expand(void *content)
{
	t_list	*casted_arg;

	casted_arg = (t_list *)content;
	if (casted_arg)
	{
		if ((t_expand *)casted_arg->content)
		{
			if (((t_expand *)casted_arg->content)->key)
				free(((t_expand *)casted_arg->content)->key);
			if (((t_expand *)casted_arg->content)->value)
				free(((t_expand *)casted_arg->content)->value);
		}
		//free(casted_arg);
	}
}

void	del_expand(void *expand)
{
	if ((t_expand *)expand)
	{
		if (((t_expand *)expand)->key)
			free(((t_expand *)expand)->key);
		if (((t_expand *)expand)->value)
			free(((t_expand *)expand)->value);
		free((t_expand *)expand);
	}
}

void	global_free(t_data *data)
{
	if (data)
	{
		if (data->env)
			ft_lstclear(&data->env, &del_expand);
		if (data->local_expands)
			ft_lstclear(&data->local_expands, &del_expand);
		if (data->prompt_line)
			free(data->prompt_line);
		if (data->expanded_line)
			free(data->expanded_line);
		if (data->words != NULL)
			ft_free_ptr(&data->words);
		free(data);
		exit(1);
	}
}
