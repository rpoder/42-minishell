/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/21 22:11:13 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data *global_data = NULL;

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
		expands = ((t_cmd_node *)cmds->content)->expand_declarations;
		printf("\nexpand_declarations = ");
		while (expands)
		{
			printf("%s ", ((t_expand *)expands->content)->key);
			printf("=");
			printf("%s ", ((t_expand *)expands->content)->value);
			expands= expands->next;
		}
		printf("\n\n");
		i++;
		cmds = cmds->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

	data = init_data(env);
	global_data = data;
	while (1)
	{
		create_parent_signals();
		// line = "echo coucou > infile";
		line = readline("minilsshell> ");
		if (!line)
			global_free(data, NO_ERR);
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

				parser(data);
				//	test_parser(data->cmds);
				executer(data);
			}
		}
		free_line_datas(data); //
	}
	global_free(data, END);
	rl_clear_history();
}
