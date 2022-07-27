/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/27 16:35:54 by ronanpoder       ###   ########.fr       */
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

/* init.c */
t_data	*init_data(void);

/* metachar_interpreter.c */
char 	*metachar_interpreter(t_data *data, char *src);
char	*find_dollar_value(t_list *shellvars, char *dollar_key);

/* metachar_interpreter_utils.c */
int		has_metachar(char *str);
int		is_to_interpret(char *str, int i, int sgl_quote, int dbl_quote);
int		is_separator(char c);
char	*find_dollar_key(char *str, int i);

/* metachar_interpreter_len.c */
int		dollar_key_len(char *str, int i);
int		dollar_value_len(t_data *data, char *str, int i);
int		interpreted_dst_len(t_data *data, char *str);



#endif



