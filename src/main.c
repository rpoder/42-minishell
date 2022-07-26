/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/26 16:56:45 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char *test;
	t_data	*data;

	/* Delete */
	t_shellvar	*shellvar1;
	shellvar1 = malloc(sizeof(t_shellvar));
	shellvar1->key = "VAR";
	shellvar1->value = "coucou";

	data = init_data();
	data->shellvars = ft_lstnew(shellvar1);
	test = "echo $VAR";

	metachar_interpreter(data, test);
	printf("len arg %d", ft_strlen(test));

	//echo coucou
	return (0);
}
