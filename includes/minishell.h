/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/08/31 13:48:44 by mpourrey         ###   ########.fr       */
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
	char	*key;
	char	*value;
}	t_expand;

typedef struct s_data {
	t_list	*env;
	t_list	*local_expands;
	char	*prompt_line;
	char	*expanded_line;
	char	**words;
}	t_data;

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
void			add_expand(t_data *data, t_list **alst, char *key, char *value);

/* expander.c */
void			expander(t_data *data);

/* expander_utils.c*/
int				has_expand(char *str);
int				is_expand_to_interpret(char *str, int i, t_quotes *quotes);
char			*get_expand_value(t_data *data, char *expand_key);
char			*get_expand_key(char *str, int i);
int				is_separator(char c);

/* expander_utils_2.c */
int				expand_key_len(char *str, int i);
int				expand_value_len(t_data *data, char *str, int i);
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
void			global_free(t_data *data);
void			del_one_expand(void *content);

/* BUILT_INS */
/* builtins_err.c */
int				check_t_expand_key_input(char *key);

/* OTHER BUILT_INS */
void			ft_echo(char **args, int fd);
void			ft_env(t_data *data, int fd);
void			ft_export(t_data *data, char *key_to_export);
int				ft_unset(t_data *data, char **args);
void			ft_cd(t_data *data, char **args);

#endif
