void	test_parser(t_list *cmds)
{
	int	i;
	int	j;
	t_list	*heredoc;
	t_list	*expands;

	i = 0;
	while (cmds)
	{
		j = 0;
		printf("CMD %d\n", i);
		printf("path = %s\n", ((t_cmd_node *)cmds->content)->path);
		if (((t_cmd_node *)cmds->content)->cmd_tab)
		{
			while (((t_cmd_node *)cmds->content)->cmd_tab[j])
			{
				printf("cmd_tab[%d] = %s\n", j, ((t_cmd_node *)cmds->content)->cmd_tab[j]);
				j++;
			}
		}
		printf("fd_in = %d\n", ((t_cmd_node *)cmds->content)->fd_in);
		printf("fd_out = %d\n", ((t_cmd_node *)cmds->content)->fd_out);
		heredoc = ((t_cmd_node *)cmds->content)->heredocs;
		printf("heredocs = ");
		while (heredoc)
		{
			printf("%s ",((char *)heredoc->content));
			heredoc = heredoc->next;
		}
	/* 	expands = ((t_cmd_node *)cmds->content)->expand_declaration;
		printf("\nexpand_declaration = ");
		while (expands)
		{
			printf("%s", ((t_expand *)expands->content)->key);
			printf("=");
			printf("%s ", ((t_expand *)expands->content)->value);
			printf(", ");
			expands= expands->next;
		} */
		printf("\n\n");
		i++;
		cmds = cmds->next;
	}
}

void	test_local_expands(t_data *data)
{
	t_list	*alst;

	alst = data->local_expands;
	if (!alst)
		return;
	ft_printf_fd("LOCAL_EXPANDS\n", 2);
	while (alst)
	{
		ft_printf_fd("%s=%s\n", 2, ((t_expand *)alst->content)->key, ((t_expand *)alst->content)->value);
		alst = alst->next;
	}
}