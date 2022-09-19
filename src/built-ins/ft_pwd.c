/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:10:38 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/18 20:32:38 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path(t_data *data, char **path)
{
	char	*buf;

	buf = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!buf)
		return (MALLOC_ERR);
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		free(buf);
		return (ERR_NOT_DEFINED);
	}
	*path = ft_strdup(buf);
	free(buf);
	return (NO_ERR);
}

int	ft_pwd(t_data *data, char **args)
{
	char	*path;
	int		ret;

	ret = set_path(data, &path);
	if (ret != NO_ERR)
	{
		if (ret == MALLOC_ERR)
			global_free(data, MALLOC_ERR);
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
	return (NO_ERR);
}
