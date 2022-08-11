/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/11 17:52:30 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data;

int	main(int argc, char **argv, char **env)
{
	char *line;
	(void)argc;
	(void)argv;

	data = init_data(env);
	// line = readline("mi_nils_shell j'écoute ? > ");
	// add_history(line);
	line =" coucoucoucou";
	printf("LINE = %s\n", line);
	if (syntax_checker(line))
	{
		//free
		printf("Marche pas\n");
		return (1);
	}
	metachar_interpreter(line);
	lexer(line);

	/* TEST ECHO */
	// char **args;
	// args = malloc(sizeof(char *) * 3);
	// args[0] = alloc_and_fill("echo");
	// args[1] = alloc_and_fill("-n");
	// args[2] = alloc_and_fill("toz");
	// args[3] = alloc_and_fill("toz");
	// args[4] = alloc_and_fill("toz");
	// ft_echo(args, 1);

	ft_env(data, 1);





	//free(line);

	// Delete
/* 	char **test;
	test = ft_split_quote(data->prompt_line, ' ');
	int	i = 0;
	while (test[i])
	{
		printf("splitted quotes %s\n", test
		i++;
	} */
	//global_free();
	// printf("env %p\n", (data->env));
	// printf("env %s\n", ((t_shellvar *)data->env->content)->key);
	return 0;
}
//test = "echo \"$VSCODE_GIT_ASKPASS_EXTRA_ARGS\" $PATH";
