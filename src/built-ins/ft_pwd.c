/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:10:38 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/14 10:27:05 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_data *data)
{
	int		i;
	char	*buf;

	i = 0;
	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		global_free(data, MALLOC_ERR);
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

	if (ft_strcmp(args[0], "pwd") != 0)
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
