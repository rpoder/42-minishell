/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:33:22 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/18 18:27:25 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_with_expand_cdpath(char *cdpath, char *arg, char **tmp)
{
	char	**cdpath_tab;
	int		i;
	int		ret;

	if (!cdpath)
		return (NO_ERR);
	cdpath_tab = ft_split(cdpath, ':');
	if (!cdpath_tab)
		return (MALLOC_ERR);
	i = 0;
	while (cdpath_tab[i])
	{
		*tmp = ft_strsjoin(3, cdpath_tab[i], "/", arg);
		ret = chdir(cdpath_tab[i]);
		if (ret == 0)
		{
			ft_free_tab(&cdpath_tab);
			return (NO_ERR);
		}
		i++;
	}
	ft_free_tab(&cdpath_tab);
	return (ERR_NOT_DEFINED);
}

static void	set_expand_pwd(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_expand_value(data, "PWD");
	set_expand(data, "OLDPWD", old_pwd);
	if (set_path(data, &new_pwd) == MALLOC_ERR)
		global_free(data, MALLOC_ERR);
	set_expand(data, "PWD", new_pwd);
}

int	ft_cd(t_data *data, char **args)
{
	int		ret;
	char	*home_expand_value;
	char	*cdpath_expand_value;
	char	*tmp_err;

	tmp_err = NULL;
	home_expand_value = get_expand_value(data, "HOME");
	cdpath_expand_value = get_expand_value(data, "CDPATH");
	if (!home_expand_value && !args[1])
	{

		return (NO_ERR);
	}
	else if (home_expand_value && !args[1])
	{
		ret = chdir(home_expand_value);
		if (ret != 0)
		{
			ft_printf_fd("minilsshell: cd: ", 2);
			perror(home_expand_value);
			set_expand_pwd(data);
			return (NO_ERR);
		}
	}
	else if (args[1])
	{
		ret = chdir(args[1]);
		if (ret != 0)
		{
			ret = try_with_expand_cdpath(args[1], cdpath_expand_value, &tmp_err);
			if (ret != 0)
			{
				ft_printf_fd("minilsshell: cd: ", 2);
				perror(tmp_err);
				set_expand_pwd(data);
				return (NO_ERR);
			}
			else if (ret == MALLOC_ERR)
				global_free(data, MALLOC_ERR);
		}
	}
	return (NO_ERR);
}
