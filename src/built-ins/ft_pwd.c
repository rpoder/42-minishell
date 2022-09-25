/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:10:38 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 20:23:56 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path(char **path)
{
	char	*buf;

	*path = NULL;
	buf = ft_calloc(sizeof(char), (PATH_MAX + 1));
	if (!buf)
		return (malloc_err);
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		free(buf);
		return (err_not_defined);
	}
	*path = ft_strdup(buf);
	free(buf);
	if (!(*path))
		return (malloc_err);
	return (no_err);
}

int	ft_pwd(t_data *data)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = set_path(&path);
	if (ret != no_err)
	{
		if (ret == malloc_err)
			global_free(data, malloc_err);
		ft_printf_fd("minilsshell: pwd: path not found\n", 2);
		set_expand(data, "?", "1");
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		set_expand(data, "?", "0");
	}
	free(path);
	return (no_err);
}
