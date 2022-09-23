/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 15:05:34 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_line_datas(t_data *data)
{
	if (data)
	{
		g_close_heredoc = false;
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

void	print_free_err_message(int err)
{
	if (err == MALLOC_ERR)
		ft_printf_fd("mi_nils_shell: malloc err\n", 2);
	else if (err == PIPE_ERR)
		ft_printf_fd("mi_nils_shell: pipe err\n", 2);
	else if (err == WAITPID_ERR)
		ft_printf_fd("mi_nils_shell: waitpid err\n", 2);
	else if (err == FORK_ERR)
		ft_printf_fd("mi_nils_shell: fork err\n", 2);
}

void	global_free(t_data *data, int err)
{
	int	exit_status;

	if (err == MALLOC_ERR || err == PIPE_ERR || err == WAITPID_ERR || err == FORK_ERR)
	{
		set_expand(data, "?", "128");
		print_free_err_message(err);
	}
	if (data)
	{
		exit_status = ft_atoi(get_expand_value(data, "?"));
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
		exit(exit_status);
	}
}
