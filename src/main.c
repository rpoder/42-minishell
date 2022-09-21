/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 15:11:02 by mpourrey         ###   ########.fr       */
=======
/*   Updated: 2022/09/21 16:28:24 by rpoder           ###   ########.fr       */
>>>>>>> master
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
<<<<<<< HEAD
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
=======
	int i = 0; ///////////
>>>>>>> master

	// create_signals();
	data = init_data(env);
<<<<<<< HEAD
	data_global = data;
=======
	global_data = data;
>>>>>>> master
	while (1)
	{
	signal(SIGINT, handle_parent_sigint);
		// line = "echo coucou > infile";
		line = readline("mi_nils_shell j'écoute ? > ");
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
<<<<<<< HEAD
			//	test_parser(data->cmds);
=======
				// test_parser(data->cmds);
>>>>>>> master
				executer(data);
			}
		}
		free_line_datas(data); //
	}
	global_free(data, END);
	rl_clear_history();
}
