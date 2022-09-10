/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/10 17:26:38 by mpourrey         ###   ########.fr       */
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

void	del_cmd(void *cmd)
{
	if ((t_cmd_node *)cmd)
	{
		if (((t_cmd_node *)cmd)->path)
			free(((t_cmd_node *)cmd)->path);
		if (((t_cmd_node *)cmd)->cmd_tab)
			ft_free_tab(&((t_cmd_node *)cmd)->cmd_tab);
		if (((t_cmd_node *)cmd)->fd_in >= 0)
			close(((t_cmd_node *)cmd)->fd_in);
		if (((t_cmd_node *)cmd)->fd_out >= 0)
			close(((t_cmd_node *)cmd)->fd_out);
		free((t_cmd_node *)cmd);
	}
}

void	global_free(t_data *data, int err)
{
	if (err == MALLOC_ERR)
		ft_printf_fd("mi_nils_shell: malloc err\n", 2);
	else if (err == PARSING_ERR)
		ft_printf_fd("mi_nils_shell: parsing err\n", 2);
	else if (err == ERR_NOT_DEFINED)
		ft_printf_fd("mi_nils_shell: err not defined\n", 2);
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
			ft_free_tab(&data->words);
		if (data->cmds)
		 	ft_lstclear(&data->cmds, &del_cmd);
		free(data);
		printf("ALL FRIED\n");
		exit(1);
	}
	// close si  fd_in >= 0;
}
