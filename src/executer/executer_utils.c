/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:56 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/22 17:20:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_err_redir_or_chevron_err(t_data *data)
{
	if (ft_strcmp(get_expand_value(data, "?"), "1") == 0 ||
		ft_strcmp(get_expand_value(data, "?"), "1") == 0)
		return (1);
	return (0);
}

int	*init_pipe(t_data *data)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		global_free(data, MALLOC_ERR);
	return(pipe_fd);
}

char	**get_env_tab(t_data *data)
{
	char	**env_tab;
	t_list	*env;
	int		i;
	int		tab_len;

	i = 0;
	tab_len = ft_lstlen(data->env);
	env_tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!env_tab)
		return (NULL);
	ft_clear_tab(&env_tab, tab_len + 1);
	env = data->env;
	while (env)
	{
		env_tab[i] = ft_strsjoin(3, ((t_expand *)env->content)->key, "=", ((t_expand *)env->content)->value);
		if (!env_tab[i])
		{
			ft_free_tab(&env_tab);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (env_tab);
}

int	is_last_cmd(t_list *cmd)
{
	if (cmd->next == NULL)
		return (1);
	return (0);
}
