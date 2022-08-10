/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/10 14:11:29 by rpoder           ###   ########.fr       */
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
	line = "co\'uc\"ougg\'\"";
	printf("STR TEST = %s\n", line);
	if (syntax_checker(line))
	{
		//free
		printf("Marche pas\n");
		return (1);
	}
	//metachar_interpreter(line);
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
