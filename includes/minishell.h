/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/02 16:02:27 by ronanpoder       ###   ########.fr       */
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

enum errors { MALLOC_ERR, PARSING_ERR, ERR_NOT_DEFINED, NO_ERR };

typedef struct s_expand {
	char	*key;
	char	*value;
}	t_expand;

typedef struct s_data {
	t_list	*env;
	t_list	*local_expands;
	char	*prompt_line;
	char	*expanded_line;
	char	**words;
	t_list	*cmds;
}	t_data;

typedef struct s_cmd_node {
	char			*path;
	char			**exec_tab;
	int				fd_in;
	int				fd_out;
}	t_cmd_node;

extern t_data *data;

# define PATH_MAX 4096

# define INT_MIN -2147483648
# define INT_MAX 2147483647

/* Main.c */

/* init.c */
t_data			*init_data(char **env, char *prompt_line);
t_quotes		*init_quotes(void);
void			clear_quotes(t_quotes *quotes);
void			set_quotes(char c, t_quotes *quotes);

/* Syntax_checker */
int				syntax_checker(char *str);

/* handle_mutes_in_expand.c */
char			*get_muted_expand_value(char *value);

/* mutes_in_expand_utils.c */
t_mute_tool		*init_mute_tool(void);
void			set_mute_tool(t_mute_tool *tool, char *src);
void			clear_mute_tool(t_mute_tool *tool);
int				skip_if_space(char *value, int i);

/* handle_mutes_in_quotes.c */
void			mute_in_quotes(t_data *data);

/* handle_expand.c */
int		set_expand(t_data *data, char *key, char *value_to_modify);
void	add_expand(t_data *data, t_list **alst, char *key, char *value);

/* expander.c */
void			expander(t_data *data);

/*expand_getters.c*/
char			*get_expand_value(t_data *data, char *expand_key);
char			*get_expand_key(char *str, int i);
int				expand_key_len(char *str, int i);
int				expand_value_len(t_data *data, char *str, int i);

/* expander_utils.c*/
int				has_expand(char *str);
int				is_expand_to_interpret(char *str, int i, t_quotes *quotes);
int				is_expand_separator(char c);
int				is_expand_suffix(char c, int j);

/* expander_utils_2.c */
t_expand_tool	*init_expand_tool(void);
void			clear_expand_tool(t_expand_tool *tool);

/* set_env.c */
void			set_env(t_data *data, char **env);

/*lexer.c*/
void			lexer(t_data *data);

/* split_words_utils.c */
t_split_tool	*init_split_tool(void);
void			set_tool_for_next_word(t_split_tool *split_tool, int i);
int				redirection_word_len(char *str, int i);

/*word_skippers */
int				skip_space(char *str, int i);
int				skip_quotes_word(char *str, int i);
int				skip_separator(char *str, int i);
int				skip_redirection_word(char *str, int i);

/* word_getters_1.c */
char			*get_and_skip_word(t_data *d, char *s, t_split_tool *tool);
char			*get_word_til_redir_op(t_data *d, char *s, t_split_tool *tool);
char			*get_word_if_end_of_src(t_data *d, char *s, t_split_tool *tool);

/* word_getters_2.c */
char			*get_word(t_data *data, char *src, t_split_tool *tool);
char			*get_redir_op_word(t_data *data, char *src, t_split_tool *tool);
char			*get_word_til_space(t_data *d, char *src, t_split_tool *tool);

/* word_trim.c */
char			*word_trim(char *src);

/* utils.c */
int				is_word_separator(char c);
int				is_redirection_operator(char c);
int				is_space(char c);

/* handle_free.c */
void			global_free(t_data *data, enum errors err);
void			del_one_expand(void *content);

/* BUILT_INS */
/* builtins_utils.c */
int	is_valid_expand_key(char *key);

/* ft_echo.c */
int	ft_echo(t_data *data, char **args);

/* ft_env.c */
void	ft_env(t_data *data, char **args);

/* ft_export.c */
int		ft_export(t_data *data, char **args);

/* ft_unset.c */
int		ft_unset(t_data *data, char **args);

/* ft_cd.c */
void	ft_cd(t_data *data, char **args);

/* ft_pwd.c */
void	ft_pwd(t_data *data, char **args);
char	*get_path(t_data *data);

/* ft_exit */
int	ft_exit(t_data *data, char **args);

/* parser.c */
int	parser(t_data *data);

#endif
