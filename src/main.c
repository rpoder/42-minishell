/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/31 13:42:59 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_lexer(char **words)
{
	int	i;

	printf("\n");
	i = 0;
	while(words[i] != NULL)
	{
		printf("word[%d] = |%s|\n", i, words[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;
	
//	while (1)
//	{
	//	line = readline("mi_nils_shell j'écoute ? > ");
	//	add_history(line);
		line = "'$?'";
		data = init_data(env, line);
	 	if (syntax_checker(line) == 1)
		{
			global_free(data);
			return (1);
		}
		mute_in_quotes(data);
		expander(data);
		printf("expanded_line = %s\n", data->expanded_line);
		lexer(data);
		test_lexer(data->words);
		global_free(data);
//	}
}

void	tests_ronan(t_data *data)
{
	/* TEST ECHO */
	// char **args;
	// args = malloc(sizeof(char *) * 3);
	// args[0] = alloc_and_fill("echo");
	// args[1] = alloc_and_fill("-n");
	// args[2] = alloc_and_fill("toz");
	// args[3] = alloc_and_fill("toz");
	// args[4] = alloc_and_fill("toz");
	// ft_echo(args, 1);

	/* TEST ENV */

	/* TEST EXPORT */
	/* t_expand *test;
	t_list	*maillon;
	test = malloc(sizeof(t_expand));
	test->key = alloc_and_fill("test");
	test->value = alloc_and_fill("coucou");
	maillon = ft_lstnew(test);
	ft_lstadd_back(&data->local_expands, maillon);

	t_expand *test2;
	t_list	*maillon2;
	test2 = malloc(sizeof(t_expand));
	test2->key = alloc_and_fill("test2");
	test2->value = alloc_and_fill("toz");
	maillon2 = ft_lstnew(test2);
	ft_lstadd_back(&data->local_expands, maillon2);

	//ft_export(data, "test2");
	//ft_env(data, 1);

	printf("\nLOCAL VARS\n");
	t_list	*tmp;
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}

	ft_unset(data, "test2");
	printf("\n\n\n");
	//ft_env(data, 1);
	printf("\nLOCAL VARS\n");
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	} */

/* 	char **args;
	args = malloc(sizeof(char *) * 6);
	args[0] = alloc_and_fill("PATH");
	args[1] = alloc_and_fill("unset");
	args[2] = alloc_and_fill("-oz");
	args[3] = alloc_and_fill("to*z");
	args[4] = alloc_and_fill("//toz");
	args[5] = NULL;
	ft_unset(data, args); */


	/* TEST CD */

}
