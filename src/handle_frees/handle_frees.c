/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:18:03 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 22:48:02 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_if_system_error(t_data *data, int err)
{
	if (err == malloc_err || err == pipe_err
		|| err == waitpid_err || err == fork_err)
	{
		set_expand(data, "?", "128");
		if (err == malloc_err)
			ft_printf_fd("mi_nils_shell: malloc err\n", 2);
		else if (err == pipe_err)
			ft_printf_fd("mi_nils_shell: pipe err\n", 2);
		else if (err == waitpid_err)
			ft_printf_fd("mi_nils_shell: waitpid err\n", 2);
		else if (err == fork_err)
			ft_printf_fd("mi_nils_shell: fork err\n", 2);
	}
}

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

void	global_free(t_data *data, int err)
{
	int	exit_status;

	handle_if_system_error(data, err);
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
