/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/27 16:50:54 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	global_free(void)
{
	if (data)
	{
		if (data->env)
			ft_lstclear(&data->env, del_one_expand);
		if (data->local_expands)
			ft_lstclear(&data->local_expands, del_one_expand);
		if (data->expanded_line)
			free(data->expanded_line);
		free(data);
	}
}
