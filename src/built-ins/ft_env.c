/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:45:13 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 18:43:05 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_one_env_line(t_list *tmp)
{
	char	*unmuted_value;

	unmuted_value = NULL;
	ft_putstr_fd(((t_expand *)tmp->content)->key, 1);
	ft_putchar_fd('=', 1);
	if (((t_expand *)tmp->content)->value)
	{
		unmuted_value = unmute_word(((t_expand *)tmp->content)->value);
		if (!unmuted_value)
			return (MALLOC_ERR);
		ft_putstr_fd(unmuted_value, 1);
		free(unmuted_value);
	}
	ft_putchar_fd('\n', 1);
	return (NO_ERR);
}

int	ft_env(t_data *data, char **args)
{
	t_list	*tmp;

	if (args[1])
	{
		ft_printf_fd("minilsshell: env: '%s': no such file or directory\n",
			2, args[1]);
		set_expand(data, "?", "127");
		return (NO_ERR);
	}
	tmp = data->env;
	while (tmp)
	{
		if (print_one_env_line(tmp) != NO_ERR)
			return (MALLOC_ERR);
		tmp = tmp->next;
	}
	set_expand(data, "?", "0");
	return (NO_ERR);
}
