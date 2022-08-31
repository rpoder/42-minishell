/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/31 13:50:22 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tests_ronan(t_data *data);

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

//	while (1)
//	{
	//	line = readline("mi_nils_shell j'écoute ? > ");
	//	add_history(line);
		line = "yo $??";
		data = init_data(env, line);
	 	if (syntax_checker(line) == 1)
		{
			global_free(data);
			return (1);
		}
		mute_in_quotes(data);
		expander(data);
		printf("expanded_line = %s\n", data->expanded_line);
		//lexer(data);
		//tests_ronan(data);
		ft_printf_fd("salut %d", 2, 214);
		global_free(data);
//	}
}

void	tests_ronan(t_data *data)
{
	add_expand(data, &data->local_expands, alloc_and_fill("TEST"), alloc_and_fill("coucou"));
	add_expand(data, &data->local_expands, alloc_and_fill("TEST2"), alloc_and_fill("salut"));

	t_list	*tmp;
	tmp = data->local_expands;
	while (tmp)
	{
		printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
		tmp = tmp->next;
	}

	char **args;
	args = malloc(sizeof(char *) * 6);
	args[0] = alloc_and_fill("[PATH]");
	args[1] = alloc_and_fill("ft_export");
	args[2] = alloc_and_fill("TE*ST");
	args[3] = alloc_and_fill("TEST2");
	args[4] = NULL;
	args[5] = NULL;

	ft_export(data, args);

	args = malloc(sizeof(char *) * 7);
	args[0] = alloc_and_fill(NULL);
	args[1] = alloc_and_fill("ft_env");
	args[2] = NULL;
	args[3] = alloc_and_fill("test");
	args[4] = alloc_and_fill("test2");
	args[5] = NULL;
	args[6] = NULL;

	ft_env(data, args);
}
