/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/30 16:46:57 by rpoder           ###   ########.fr       */
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
	// args = malloc(sizeof(char *) * 6);
	// args[0] = alloc_and_fill("[PATH]");
	// args[1] = alloc_and_fill("echo");
	// args[2] = alloc_and_fill("-n");
	// args[3] = alloc_and_fill("coucou");
	// args[4] = alloc_and_fill("toz");
	// args[5] = NULL;
	// ft_echo(args, 1);

	// ft_add_expand(&data->local_expands, alloc_and_fill("TEST"), alloc_and_fill("coucou"), false);
	// ft_add_expand(&data->local_expands, alloc_and_fill("TEST2"), alloc_and_fill("salut"), false);

	// t_list	*tmp;
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }


	/* TEST ENV */
	// char **args;
	// args = malloc(sizeof(char *) * 6);
	// args[0] = alloc_and_fill("[PATH]");
	// args[1] = alloc_and_fill("ft_unset");
	// args[2] = alloc_and_fill("87*");
	// args[3] = alloc_and_fill("/5");
	// args[4] = NULL;
	// args[5] = NULL;

	/* TEST EXPORT */

	// ft_unset(data, args);

	// args[1] = alloc_and_fill("ft_env");
	// args[2] = NULL;
	// //ft_env(data, args);

	// printf("\nLOCAL VARS\n");
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	// char **args;
	// args = malloc(sizeof(char *) * 7);
	// args[0] = alloc_and_fill(NULL);
	// args[1] = alloc_and_fill("export");
	// args[2] = alloc_and_fill("?");
	// args[3] = alloc_and_fill("test");
	// args[4] = alloc_and_fill("test2");
	// args[5] = NULL;
	// args[6] = NULL;

	// ft_export(data, args);
	// ft_unset(data, args);
	// ft_env(data, 1);

	// printf("\nLOCAL VARS\n");
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	// char **args2;
	// args2 = malloc(sizeof(char *) * 6);
	// args2[0] = alloc_and_fill("[PATH]");
	// args2[1] = alloc_and_fill("unset");
	// args2[2] = alloc_and_fill("test2");
	// args2[3] = alloc_and_fill("LS_COLORS");
	// args2[4] = alloc_and_fill("PATH");
	// args2[5] = NULL;
	// ft_unset(data, args2);

	// printf("\nLast unset\nLOCAL VARS\n");
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }



	/* TEST CD */
	char **args;
	args = malloc(sizeof(char *) * 4);
	args[0] = alloc_and_fill(NULL);
	args[1] = alloc_and_fill("ft_cd");
	args[2] = alloc_and_fill("../includes");
	args[5] = NULL;
	//ft_env(data, 1);
	ft_set_expand(data, "PWD", "groszizi");
	 ft_cd(data, args);
	//ft_pwd(args);

	// args = malloc(sizeof(char *) * 3);
	// args[0] = alloc_and_fill(NULL);
	// args[1] = alloc_and_fill("ft_env");
	// args[2] = NULL;
	// ft_env(data, args);
	printf("PWD = %s\n", get_expand_value("PWD"));
	printf("OLDPWD = %s\n", get_expand_value("OLDPWD"));
	printf("? = %s\n", get_expand_value("?"));
	printf("Actual pwd -> %s\n", get_path());
}
