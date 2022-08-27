/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:33:22 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/27 15:47:55 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dbldot_pathlen(char *str)
{
	int	len;

	len = 0;
	if (*str == '\0')
		return (-1);
	while (*str && *str != ':')
	{
		str++;
		len++;
	}
	return (len);
}

static void	concat_path_arg(char **dst, char *arg, int size, int i)
{
	int	j;

	j = 0;
	*dst[i] = '/';
	i++;
	while (i < size && arg[j])
	{
		*dst[i] = arg[j];
		i++;
		j++;
	}
	*dst[i] = '\0';
}

int	try_with_env_path(char *arg)
{
	char	*env_path;
	char	*tmp;
	int		i;
	int		ret;
	int		size;

	ret = -1;
	env_path = get_expand_value("PATH");
	if (!env_path)
		return (-1);
	printf("env_path = %s\n", env_path);
/* 	while (*env_path || ret != 0)
	{
		i = 0;
		size = dbldot_pathlen(env_path) + 1 + ft_strlen(arg);
		tmp = malloc(sizeof(char) * (size + 1));
		// proteger
		while (*env_path && *env_path != ':')
		{
			tmp[i] = *env_path;
			env_path++;
			i++;
		}
		concat_path_arg(&tmp, arg, size, i);
		ret = chdir(tmp);
		printf("tmp = %s\n", tmp);
		free(tmp);
		env_path++;
	} */
	return (1);
}

void	ft_cd(t_data *data, char **args)
{
	char	*home_expand;
	int		ret;

	ret = -1;
	// if (!home_expand && !args[2])
	// 	return ;
	// if (home_expand && !args[2])
	// 	ret = chdir(home_expand);
	try_with_env_path(args[2]);
/* 	if (args[2][0] == '/')
	{
		if (chdir(args[2]) != 0)
		// err message
	} */

	// printf("args[2] = %s\n", args[2]);
	// printf("ret chedir %d\n",chdir(args[2]));
}
