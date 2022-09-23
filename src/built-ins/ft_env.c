/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:45:13 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 16:33:57 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	t_list	*tmp;
	char	*unmuted_value;

	if (args[1])
	{
		ft_printf_fd("minilsshell: env: '%s': no such file ordirectory\n",
			2, args[1]);
		set_expand(data, "?", "127");
		return (NO_ERR);
	}
	tmp = data->env;
	while (tmp)
	{
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
		tmp = tmp->next;
	}
	set_expand(data, "?", "0");
	return (NO_ERR);
}
