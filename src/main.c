/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/13 18:47:27 by ronanpoder       ###   ########.fr       */
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

void	test_unmute_lexer(char **words)
{
	int	i;
	int	j;
	char c;

	i = 0;
	while (words[i] != NULL)
	{
		j = 0;
		printf("unmute word[%d] = ", i);
		while (words[i][j] != '\0')
		{
		 	if (words[i][j] > 127)
			{
				printf("entre\n");
				c = words[i][j] - 127;
			}
			else if (words[i][j] < 0)
				c = words[i][j] * -1;

			else
				c = words[i][j];
			printf("%c", c);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
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

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

	while (1)
	{
		// line = readline("mi_nils_shell j'écoute ? > ");
		// add_history(line); //pas strlen < 1
		line = "cat test | grep t";
		data = init_data(env, line);
	 	if (quote_syntax_checker(line) == 1) //quote_syntax_checker
		{
			global_free(data, PARSING_ERR);
			return (1);
		}
		mute_in_quotes(data);
		expander(data);
		lexer(data);
	//	test_lexer(data->words);
		redirection_syntax_printer(data->words);
		parser(data);

	//	test_unmute_lexer(data->words);
		executer(data);
		//test_parser(data->cmds);
		global_free(data, END);
	}
}

void	tests_ronan(t_data *data)
{
	add_expand(data, &data->local_expands, ft_alloc_and_fill("TEST"), ft_alloc_and_fill("coucou"));
	add_expand(data, &data->local_expands, ft_alloc_and_fill("TEST2"), ft_alloc_and_fill("salut"));

	// t_list	*tmp;
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	char **args;
	args = malloc(sizeof(char *) * 6);
	args[0] = ft_alloc_and_fill("[PATH]");
	args[1] = ft_alloc_and_fill("ft_exit");
	args[2] = ft_alloc_and_fill("8999999999999999999999999999999999999999999999");
	args[3] = ft_alloc_and_fill("coucou");
	args[4] = ft_alloc_and_fill("coucou");
	args[5] = NULL;

	ft_exit(data, args);
	printf("PAS EXIT\n");
	// args = malloc(sizeof(char *) * 7);
	// args[0] = ft_alloc_and_fill(NULL);
	// args[1] = ft_alloc_and_fill("ft_env");
	// args[2] = NULL;
	// args[3] = ft_alloc_and_fill("test");
	// args[4] = ft_alloc_and_fill("test2");
	// args[5] = NULL;
	// args[6] = NULL;

	// ft_env(data, args);
}
