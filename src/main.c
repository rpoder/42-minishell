/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/03 16:13:10 by ronanpoder       ###   ########.fr       */
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
	// line = readline("mi_nils_shell j'écoute > ");
	// add_history(line);
	line = "\"co\'uc\'ou\" coucou";
	printf("STR TEST = %s\n", line);
	metachar_interpreter(line);
	ft_split_quote(data->prompt_line);
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
