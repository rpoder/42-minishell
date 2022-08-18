/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/18 16:22:40 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_expand(void *content)
{
	t_expand	*casted_content;

	casted_content = ((t_expand *)content);
	if (casted_content)
	{
		if (casted_content->key)
			free(casted_content->key);
		if (casted_content->value)
			free(casted_content->value);
		free(content);
	}
}

void	global_free(void)
{
	if (data)
	{
		if (data->env)
			ft_lstclear(&data->env, del_expand);
		if (data->local_expands)
			ft_lstclear(&data->local_expands, del_expand);
		if (data->expanded_line)
			free(data->expanded_line);
		free(data);
	}
}
