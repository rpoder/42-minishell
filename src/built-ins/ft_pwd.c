/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:10:38 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/30 18:45:29 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_data *data)
{
	int		i;
	char	*buf;

	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		global_free(data);
	while (getcwd(buf, i) == 0 || i > PATH_MAX)
	{
		free(buf);
		buf = malloc(sizeof(char) * (i + 1));
		i++;
	}
	if (i >= PATH_MAX)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

void	ft_pwd(t_data *data, char **args)
{
	char	*path;

	if (ft_strcmp(args[1], "ft_pwd") != 0)
		return ;
	path = get_path(data);
	if (!path)
	{
		ft_putstr_fd("pwd: path not found\n", 1);
		set_expand(data, "?", "1");
	}
	else
	{
		ft_putstr_fd(path, 1);
		set_expand(data, "?", "0");
	}
	free(path);
}
