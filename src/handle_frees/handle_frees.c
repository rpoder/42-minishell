/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/01 17:40:48 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_shellvar(void *content)
{
	t_shellvar *casted_content;

	casted_content = ((t_shellvar *)content);
	if (casted_content)
	{
		if (casted_content->key)
			free(casted_content->key);
		if (casted_content->value)
			free(casted_content->value);
	}
}

void	global_free(void)
{
	if (data)
	{
		if (data->env)
			ft_lstclear(&data->env, del_shellvar);
	}
}
