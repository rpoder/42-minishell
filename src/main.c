/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/17 12:30:44 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_parser(t_list *cmds)
{
	int	i;
	int	j;
	t_list	*heredoc;

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
		printf("\n\n");
		i++;
		cmds = cmds->next;
	}
}

void	test_lexer(char **words)
{
	int	i;

	printf("\n");
	i = 0;
	while (words[i] != NULL)
	{
		printf("word[%d] = |%s|\n", i, words[i]);
		i++;
	}
}

void	test_ronan(t_data *data)
{

	// t_list	*tmp;
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	char **args;
	args = malloc(sizeof(char *) * 2);
	args[0] = ft_alloc_and_fill("env");
	args[1] = NULL;

	ft_env(data, args);

}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

	while (1)
	{
		// line = readline("mi_nils_shell j'écoute ? > ");
		// add_history(line); //pas strlen < 1
		line = "echo $USER| echo $USER";
		data = init_data(env, line);
	 	if (quote_syntax_checker(line) == 1) //quote_syntax_checker
		{
			global_free(data, PARSING_ERR);
			return (1);
		}
		// test_ronan(data);

 		mute_in_quotes(data);
		expander(data);
		lexer(data);
	//	test_lexer(data->words);
		redirection_syntax_printer(data->words);
		parser(data);
		executer(data);
	//	test_parser(data->cmds);
		global_free(data, END);
	}
}

