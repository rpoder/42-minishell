/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/26 18:01:05 by ronanpoder       ###   ########.fr       */
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
# include "utils.h"

typedef struct s_expand {
	char *key;
	char *value;
}	t_expand;

typedef struct s_data {
	t_list	*env;
	t_list	*local_expands;
	char	*prompt_line;
	char	*expanded_line;
	char	**tokens;
}	t_data;

extern t_data *data;

# define PATH_MAX 4096

/* Main.c */

/* init.c */
t_data		*init_data(char **env, char *prompt_line);
t_quotes	*init_quotes(void);

/* Syntax_checker */
int		syntax_checker(char *str);

/* handle_mutes.c */
void	mute_non_interpretable_quotes(t_data *data);
char	*get_muted_expand_value(char *value);

/* handle_expand.c */
void	ft_add_expand(t_list **alst, char *key, char *value, bool manual_add);
int		ft_set_expand(t_data *data, char *key, char *value_to_modify);

/* expander.c */
void	expander(char *src);

/* expander_utils.c*/
int		has_expand(char *str);
int		is_to_interpret(char *str, int i, int sgl_quote, int dbl_quote);
char	*get_expand_value(char *expand_key);
char	*get_expand_key(char *str, int i);
int		is_separator(char c);

/* expander_utils_2.c */
int	expand_key_len(char *str, int i);
int	expand_value_len(char *str, int i);

/* set_env.c */
void	set_env(t_data *data, char **env);

/*lexer.c*/
void	lexer(char *str);

/* split_tokens.c */
char	**split_tokens(char *str);

/* split_tokens_utils.c */
int				token_trim_len(char *str);
char			*token_trim(char *str);
t_split_data	*init_split_data();
void			set_data_for_next_token(t_split_data *split_data, int i);
int				redirection_token_len(char *str, int i);

/*token_skippers */
int	skip_space(char *str, int i);
int	skip_quotes_token(char *str, int i);
int	skip_separator(char *str, int i);
int	skip_redirection_token(char *str, int i);

/* token_getters.c */
char	*get_token_if_end_of_str(char *str, t_split_data *data);
char	*get_token(char *str, int i, int token_start);
char	*get_and_skip_token(char *str, t_split_data *data);

/* utils.c */
t_quotes	*set_quotes(char c, t_quotes *quotes);

/* utils_2.c */
int	is_token_separator(char c);
int	is_redirection_operator(char c);
int	is_space(char c);

/* handle_free.c */
void	global_free(void);
void	del_t_expand(void *content);

/* BUILT_INS */
/* builtins_utils.c */
int	is_valid_expand_key(char *key);

/* BUILT_INS */
int		ft_echo(char **args, int fd);
void	ft_env(t_data *data, int fd);
int		ft_export(t_data *data, char **args);
int		ft_unset(t_data *data, char **args);
void	ft_cd(t_data *data, char **args);
void	ft_pwd(void);
char	*get_path();



#endif



