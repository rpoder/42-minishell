/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/18 14:11:44 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_shellvar {
	char *key;
	char *value;
}	t_shellvar;

// a checker norminettouille "bool	sgl_quote = false";

typedef struct s_quotes {
	bool	sgl_quote;
	bool	dbl_quote;
}	t_quotes;

typedef struct s_data {
	t_list	*env;
	t_list	*local_vars;
	char	*prompt_line;
	char	**lexed_line;
}	t_data;

extern t_data *data;

/* Main.c */

/* Syntax_checker */
int	syntax_checker(char *str);

/* utils.c */
void		add_shellvar(t_list **alst, char *key, char *value);
t_quotes	*set_quotes(char c, t_quotes *quotes);

/* init.c */
t_data		*init_data(char **env);
t_quotes	*init_quotes(void);

/* metachar_interpreter.c */
void	metachar_interpreter(char *src);

/* set_prompt_line_utils.c */
int		has_metachar(char *str);
int		is_to_interpret(char *str, int i, int sgl_quote, int dbl_quote);
char	*get_dollar_value(char *dollar_key);
char	*get_dollar_key(char *str, int i);
int		is_separator(char c);

/* set_prompt_line_utils_2.c */
int	dollar_key_len(char *str, int i);
int	dollar_value_len(char *str, int i);

/* set_env.c */
void	set_env(t_data *data, char **env);

/*lexer.c*/
void	lexer(char *str);

/* ft_split_quote */
char **ft_split_quote(char *str);

/* ft_split_quotes_utils */
int	is_split_separator(char c);
int	is_split_space(char c);

/* handle_free.c */
void	global_free(void);
void	del_shellvar(void *content);

/* BUILT_INS */
/* echo.c */
void	ft_echo(char **args, int fd);
void	ft_env(t_data *data, int fd);
void	ft_export(t_data *data, char *key_to_export);
void	ft_unset(t_data *data, char *key_to_unset);

#endif



