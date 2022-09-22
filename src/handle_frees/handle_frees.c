/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/21 22:50:02 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_line_datas(t_data *data)
{
	if (data)
	{
		if (data->prompt_line)
			free(data->prompt_line);
		data->prompt_line = NULL;
		if (data->expanded_line)
			free(data->expanded_line);
		data->expanded_line = NULL;
		if (data->words != NULL)
			ft_free_tab(&data->words);
		data->words = NULL;
		if (data->cmds)
		 	ft_lstclear(&data->cmds, &del_cmd);
		data->cmds = NULL;
	}
}

void	global_free(t_data *data, enum errors err)
{
	if (err == MALLOC_ERR)
		ft_printf_fd("mi_nils_shell: malloc err\n", 2);
	// else if (err == PARSING_ERR)
	// 	ft_printf_fd("mi_nils_shell: parsing err\n", 2);
	// else if (err == ERR_NOT_DEFINED)
	// 	ft_printf_fd("mi_nils_shell: err not defined\n", 2);
	// else if (err == PIPE_ERR)
	// 	ft_printf_fd("mi_nils_shell: pipe err\n", 2);
	// else if (err == WAITPID_ERR)
	// 	ft_printf_fd("mi_nils_shell: waitpid err\n", 2);
	// else if (err == FORK_ERR)
	// ft_printf_fd("mi_nils_shell: fork err\n", 2);
	// else if (err == END)
	// 	ft_printf_fd("mi_nils_shell: Bravo :)\n", 2);
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
		exit(1);
	}
}
