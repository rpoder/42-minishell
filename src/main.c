/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/18 19:37:50 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data;

int	main(int argc, char **argv, char **env)
{
	char *line;
	(void)argc;
	(void)argv;

//	line = readline("mi_nils_shell j'écoute ? > ");
//	add_history(line);
	line ="$?";
	data = init_data(env, line);
	printf("line = |%s|\n", line);
	if (syntax_checker(line) == 1)
	{
		//free
		return (1);
	}
	mute_non_interpretable_quotes(data);
	expander(data->prompt_line);
	printf("expanded_line = |%s|\n", data->expanded_line);
	lexer(data->expanded_line);
	

	/* TEST ECHO */
	// char **args;
	// args = malloc(sizeof(char *) * 3);
	// args[0] = alloc_and_fill("echo");
	// args[1] = alloc_and_fill("-n");
	// args[2] = alloc_and_fill("toz");
	// args[3] = alloc_and_fill("toz");
	// args[4] = alloc_and_fill("toz");
	// ft_echo(args, 1);

	//ft_env(data, 1);


	/* TEST EXPORT */
/* 	t_expand *test;
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
	ft_export(data, "?");
	ft_env(data, 1);

	printf("\nLOCAL VARS\n");
	t_list	*tmp;
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	} */




	//free(line);

	// Delete
/* 	char **test;
	test = ft_split_quote(data->expanded_line, ' ');
	int	i = 0;
	while (test[i])
	{
		printf("splitted quotes %s\n", test
		i++;
	} */
	//global_free();
	// printf("env %p\n", (data->env));
	// printf("env %s\n", ((t_expand *)data->env->content)->key);
	return 0;
}
//test = "echo \"$VSCODE_GIT_ASKPASS_EXTRA_ARGS\" $PATH";
