/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/28 14:27:01 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char *test;
	t_data	*data;

	data = init_data();

	/* Delete */
	t_shellvar	*shellvar1;
	shellvar1 = malloc(sizeof(t_shellvar));
	shellvar1->key = "VAR";
	shellvar1->value = "coucou";
	data->shellvars = ft_lstnew(shellvar1);
	t_shellvar *shellvar2;
	t_list	*node2;
	shellvar2 = malloc(sizeof(t_shellvar));
	shellvar2->key = "VAR2";
	shellvar2->value = "toz";
	node2 = ft_lstnew(shellvar2);
	ft_lstadd_back(&data->shellvars, node2);

	/* si readline declaration de variable (avec =), lstnew puis lstaddback de shellvars */

	test = "echo \"$$$$VAR\"";

	printf("src_len = %d\n", ft_strlen(test));
	metachar_interpreter(data, test);
	return (0);
}
