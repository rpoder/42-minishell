/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/26 19:26:26 by margot           ###   ########.fr       */
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
	/* si readline declaration de variable (avec =), lstnew puis lstaddback de shellvars */
	
	data->shellvars = ft_lstnew(shellvar1);
	test = "echo $VAR";
	
	printf("src_len = %d\n", ft_strlen(test));
	metachar_interpreter(data, test);
	return (0);
}
