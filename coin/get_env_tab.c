/* char	**get_env_tab(t_data *data)
{
	char	**env_tab;
	t_list	*env;
	int		i;
	int		tab_len;

	i = 0;
	tab_len = ft_lstlen(data->env);
	env_tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!env_tab)
		return (NULL);
	ft_clear_tab(&env_tab, tab_len + 1);
	env = data->env;
	while (env)
	{
		env_tab[i] = ft_strsjoin(3, ((t_expand *)env->content)->key, "=", ((t_expand *)env->content)->value);
		if (!env_tab[i])
		{
			ft_free_tab(&env_tab);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (env_tab);
} */
