/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/16 16:54:17 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft.h"
# include "utils.h"

enum errors { MALLOC_ERR = -100, OPEN_ERR, PARSING_ERR, ERR_NOT_DEFINED, NO_ERR, END, PIPE_ERR, DUP_ERR, WAITPID_ERR, CLOSE_ERR};

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
	char	*path;
	char	**cmd_tab;
	int		fd_in;
	int		fd_out;
	t_list	*heredocs;
}	t_cmd_node;

extern t_data *data;

// # define PATH_MAX 4096

# define FD_UNDEFINED -2
# define FD_PARSING_ERR -3

# define BUFFER_SIZE_GNL 10

/* init.c */
t_data			*init_data(char **env, char *prompt_line);
t_quotes		*init_quotes(void);
void			clear_quotes(t_quotes *quotes);
void			set_quotes(char c, t_quotes *quotes);

/* quote_syntax_checker */
int				quote_syntax_checker(char *str);
/* redir_op_syntax_error.c */
void			redirection_syntax_printer(char **words);

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
int				set_expand(t_data *data, char *key, char *value_to_modify);
void			add_expand(t_data *data, t_list **alst, char *key, char *value);

/*---------------------------------------------- EXPANDER */
/* expander.c */
void			expander(t_data *data);

/*expand_getters.c*/
char			*get_expand_value(t_data *data, char *expand_key);
char			*get_expand_key(char *str, int i);

/* expand_len.c */
int				expand_key_len(char *str, int i);
int				expand_value_len(t_data *data, char *str, int i);
int				expanded_line_len(t_data *data, char *str, t_expand_tool *tool);

/* expander_utils.c*/
int				has_expand(char *str);
int				is_expand_to_interpret(char *str, int i, t_quotes *quotes);
int				is_expand_separator(char c);
int				is_expand_suffix(char c, int j);

/* expander_tool_utils.c */
t_expand_tool	*init_expand_tool(void);
void			clear_expand_tool(t_expand_tool *tool);
void			free_expand_tool(t_expand_tool *expand_tool);

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

/*----------------------------------------------PARSER*/

/* parser.c */
int				parser(t_data *data);

/* set_cmd_node.c */
int				set_and_skip_cmd_node(char **words, t_cmd_node *cmd, int *i);

/* set_cmd_tab */
int	set_cmd_tab(char **words, int i, t_cmd_node *cmd);

/* set_redirection */
int	check_and_set_redirection(char **words, int i, t_cmd_node *cmd);

/* open_files.c */
int				set_fd_heredoc(t_cmd_node *cmd, char *lim);
int				set_fd_in(t_cmd_node *cmd, char *infile);
int				set_fd_out(t_cmd_node *cmd, char *outfile, int flag);

/* parser_utils.c */
int				cmd_tab_len(char **words, int i);
t_cmd_node		*init_cmd_node(void);
char			*unmute_word(char *str);
void			print_ambiguous_redirection(char *expand);

/* heredoc_utils */
void			free_heredoc_tool(t_heredoc_tool *tool);
t_heredoc_tool	*init_heredoc_tool(char *lim);
char			*get_heredoc_name(int i);

/* set_all_cmd_path.c */
void			set_all_cmd_path(t_data *data);

/*----------------------------------------------UTILS*/

/* utils.c */
int				is_word_separator(char c);
int				is_redirection_operator(char c);
int				is_space(char c);
int				is_pipe(char c);

/* gnl_minishell.c */
char			*gnl_minishell(int fd, int *ret);

/* gnl_minishell_utils.c */
char			*ft_strjoin_gnl(char *s1, char *s2, int *ret);
char			*ft_fill_dst(char *s1, char *s2, char *dst);
char			*ft_strndup_gnl(char *str, int start, int len, int *ret);

/* handle_free.c */
void			global_free(t_data *data, int err);
void			del_one_expand(void *content);
void			del_cmd(void *cmd);

/*----------------------------------------------BUILT_INS */

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
int		ft_exit(t_data *data, char **args);

/*----------------------------------------------EXECUTER */

/* executer.c */
void	executer(t_data *data);

/* handle_redirections.c */
void	redirect_pipe_out(t_data *data, int *pipe_fd);
void	chevron_redirection(t_data *data, t_cmd_node *cmd);

/* executer_utils.c */
char	**get_env_tab(t_data *data);
int		is_first_cmd(t_data *data, t_list *cmd);
int		is_last_cmd(t_list *cmd);
int		*init_pipe(t_data *data);

/* executer_tool_utils.c */
t_exec_tool	*init_tool(t_list *cmd);


#endif
