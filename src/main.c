/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 02:30:31 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_bool = false;

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
		while (((t_cmd_node *)cmds->content)->cmd_tab[j])
		{
			printf("cmd_tab[%d] = %s\n", j, ((t_cmd_node *)cmds->content)->cmd_tab[j]);
			j++;
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

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

	data = init_data(env);
	while (1)
	{
		custom_all_sigs();
		// line = "echo coucou > infile";
		line = readline("minilsshell> ");
		if (!line)
		{
			rl_clear_history();
			global_free(data, NO_ERR);
		}
		if (ft_strlen(line) >= 1)
		{
			add_history(line);
			data->prompt_line = line;
			if (!data->prompt_line)
				global_free(data, MALLOC_ERR);
	 		if (quote_syntax_checker(line) == 0)
			{
 				mute_in_quotes(data);
				expander(data);
				lexer(data);
				redirection_syntax_printer(data->words);
				if (parser(data) == 0)
					executer(data);
			}
		}
		free_line_datas(data); //
	}
	global_free(data, END);
	rl_clear_history();
}
