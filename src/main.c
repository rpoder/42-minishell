/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/19 18:59:54 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data;

void	tests_ronan(t_data *data);

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
	// if (syntax_checker(line) == 1)
	// {
		// free
		// return (1);
	// }
	// mute_non_interpretable_quotes(data);
	// expander(data->prompt_line);
	// printf("expanded_line = |%s|\n", data->expanded_line);
	// lexer(data->expanded_line);

	tests_ronan(data);
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
	//ft_env(data, 1);

	/* TEST EXPORT */
	ft_add_expand(&data->local_expands, alloc_and_fill("test"), alloc_and_fill("coucou"), false);
	ft_add_expand(&data->local_expands, alloc_and_fill("test2"), alloc_and_fill("salut"), false);


	printf("\nLOCAL VARS\n");
	t_list	*tmp;
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}


	char **args;
	args = malloc(sizeof(char *) * 7);
	args[0] = alloc_and_fill("[PATH]");
	args[1] = alloc_and_fill("unset");
	args[2] = alloc_and_fill("PATH");
	args[3] = alloc_and_fill("?");
	args[4] = alloc_and_fill("USER");
	args[5] = alloc_and_fill("*test2");
	args[6] = NULL;
	ft_unset(data, args);

	printf("\nLOCAL VARS\n");
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}
	ft_env(data, 1);



	/* TEST CD */

}
