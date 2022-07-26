/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/26 16:57:02 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdbool.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include "libft.h"

typedef struct s_shellvar {
	char *key;
	char *value;
}	t_shellvar;

typedef struct s_data {
	t_list	*shellvars;
}	t_data;

/* Main.c */

/* Init.c */
t_data	*init_data(void);

/* Interpretor.c */
char *metachar_interpreter(t_data *data, char *src);



#endif



