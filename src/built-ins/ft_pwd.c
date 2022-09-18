/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:10:38 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/18 16:05:53 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path(t_data *data, char **path)
{
	int		i;
	char	*buf;

	i = 0;
	buf = malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (MALLOC_ERR);
	while (getcwd(buf, i) == 0 || i > PATH_MAX)
	{
		free(buf);
		buf = malloc(sizeof(char) * (i + 1));
		if (!buf)
			return (MALLOC_ERR);
		i++;
	}
	if (i >= PATH_MAX)
	{
		free(buf);
		return (PATH_MAX_ERR);
	}
	*path = buf;
	return (NO_ERR);
}

void	ft_pwd(t_data *data, char **args)
{
	char	*path;
	int		ret;

	if (ft_strcmp(args[0], "pwd") != 0)
		return ;
	ret = set_path(data, &path);
	if (ret != NO_ERR)
	{
		if (ret == MALLOC_ERR)
			global_free(data, MALLOC_ERR);
		ft_putstr_fd("pwd: path not found\n", 1);
		set_expand(data, "?", "1");
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 2);
		set_expand(data, "?", "0");
	}
	free(path);
}
