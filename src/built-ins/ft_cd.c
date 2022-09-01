/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:33:22 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/01 11:21:21 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_point(char *arg)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * (1 + ft_strlen(arg) + 1));
	if (!dst)
		return (NULL);
	dst[i] = '.';
	i++;
	while (arg[i - 1])
	{
		dst[i] = arg[i - 1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	try_cd(t_data *data, char *arg)
{
	int		ret;
	char	*old_path;
	char	*concatened;

	old_path = get_expand_value(data, "PWD");
	if (!old_path)
		return (-1);
	if (arg[0] != '.')
	{
		concatened = add_point(arg);
		if (!concatened)
		{
			global_free(data, MALLOC_ERR);
			return (-1);
		}
		ret = chdir(concatened);
		free(concatened);
	}
	else
		ret = chdir(arg);
	if (ret == 0)
	{
		set_expand(data, "OLDPWD", old_path);
		set_expand(data, "PWD", get_path(data));
	}
	return (ret);
}

void	ft_cd(t_data *data, char **args)
{
	char	*home_expand;
	int		ret;

	if (!home_expand && !args[2])
	{
		ft_putstr_fd("cd: HOME is not set\n", 2);
		return ;
	}
	else if (!home_expand && args[2])
		return ;
	if (home_expand && !args[2])
		ret = chdir(home_expand);
	if (try_cd(data, args[2]) != 0)
	{
		ft_putstr_fd("cd:\'", 2);
		ft_putstr_fd(args[2], 2);
		ft_putstr_fd("\': no such file or directory\n", 2);
		set_expand(data, "?", "1");
	}
	else
		set_expand(data, "?", "0");
}
