/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:33:22 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/20 14:01:20 by rpoder           ###   ########.fr       */
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

void	ft_cd_with_arg(t_data *data, char *arg)
{
	int		ret;
	char	*cdpath_expand_v;
	char	*tmp_err;

	tmp_err = NULL;
	ret = chdir(arg);
	if (ret != 0)
	{
		cdpath_expand_v = get_expand_value(data, "CDPATH");
		ret = try_with_expand_cdpath(arg, cdpath_expand_v, &tmp_err);
		if (ret != NO_ERR)
		{
			set_expand(data, "?", "127");
			ft_printf_fd("minilsshell: cd: ", 2);
			perror(tmp_err);
			set_expand_pwd(data);
			return ;
		}
		else if (ret == MALLOC_ERR)
			global_free(data, MALLOC_ERR);
	}
	set_expand_pwd(data);
	set_expand(data, "?", "0");
}

static void	ft_cd_home_no_arg(t_data *data, char *home_expand_v)
{
	int		ret;

	ret = chdir(home_expand_v);
	if (ret != 0)
	{
		set_expand(data, "?", "127");
		ft_printf_fd("minilsshell: cd: ", 2);
		perror(home_expand_v);
	}
	else
		set_expand(data, "?", "0");
}

int	ft_cd(t_data *data, char **args)
{
	int		ret;
	char	*home_expand_v;

	if (ft_tablen(args) > 2)
	{
		set_expand(data, "?", "0");
		ft_printf_fd("minilsshell: cd: too many arguments\n", 2);
		return (NO_ERR);
	}
	home_expand_v = get_expand_value(data, "HOME");
	if (!home_expand_v && !args[1])
	{
		set_expand(data, "?", "127");
		return (NO_ERR);
	}
	else if (home_expand_v && !args[1])
		ft_cd_home_no_arg(data, home_expand_v);
	else if (args[1])
		ft_cd_with_arg(data, args[1]);
	return (NO_ERR);
}
