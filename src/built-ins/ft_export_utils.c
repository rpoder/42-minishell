/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:43:04 by rpoder            #+#    #+#             */
/*   Updated: 2022/08/29 12:44:17 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dbldot_pathlen(char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '\0')
		return (-1);
	while (str[i] && str[i] != ':')
	{
		i++;
		len++;
	}
	return (len);
}

static char	*get_env_path_part(char *env_path, int *i)
{
	int			j;
	char		*tmp;

	tmp = malloc(dbldot_pathlen(env_path, *i) + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	while (env_path[*i] && env_path[*i] != ':')
	{
		tmp[j] = env_path[*i];
		*i = *i + 1;
		j++;
	}
	tmp[j] = '\0';
	(*i)++;
	return (tmp);
}

char	*concatenated_path(char *env_path_part, char *arg)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(env_path_part) + 1 + ft_strlen(arg) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (env_path_part[i])
	{
		tmp[j] = env_path_part[i];
		i++;
		j++;
	}
	tmp[j] = '/';
	j++;
	i = 0;
	while (arg[i])
	{
		tmp[j] = arg[i];
		i++;
		j++;
	}
	return (tmp);
}

int	try_with_env_path(char *arg)
{
	char	*env_path;
	char	*env_path_part;
	char	*tmp;
	int		ret;
	int		*i;

	env_path = get_expand_value("PATH");
	tmp = NULL;
	env_path_part = NULL;
	if (!env_path)
		return (1);
	i = malloc(sizeof(int));
		return(-1);
	*i = 0;
	ret = -1;
	while (ret != 0 && env_path[*i])
	{
		env_path_part = get_env_path_part(env_path, i);
		if (!env_path_part)
		{
			if (tmp)
				free(tmp);
			return(-1);
		}
		tmp = concatenated_path(env_path_part, arg);
		if (!tmp)
		{
			if (env_path_part)
				free(env_path_part);
			return(-1);
		}
		ret = chdir(tmp);
		free(tmp);
		free(env_path_part);
	}
	return (ret);
}
