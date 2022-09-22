/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/22 14:37:56 by mpourrey         ###   ########.fr       */
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


enum errors { MALLOC_ERR = -100, OPEN_ERR, PARSING_ERR, ERR_NOT_DEFINED, NO_ERR, END, PIPE_ERR, DUP_ERR, WAITPID_ERR, CLOSE_ERR, PATH_MAX_ERR, FORK_ERR};
enum builtins { CD = 1, ECHO, ENV, EXIT, EXPORT, PWD, UNSET };

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
	t_list	*expand_declarations;
}	t_cmd_node;

extern t_data *g_data;

# define PATH_MAX 4096
# define ENV_DEFAULT_PATH "/mnt/nfs/homes/rpoder/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

# define FD_UNDEFINED -2
# define FD_PARSING_ERR -3

# define BUFFER_SIZE_GNL 10

///////////////A SUPP
void	test_parser(t_list *cmds);
void	test_local_expands(t_data *data);
/////////////////////////////

/* init.c */
t_data			*init_data(char **env);
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
bool			set_on(t_list **alst, char *key, char *value_to_modify);
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
void			save_unfound_expand(t_data *data, char *str, int start, t_expand_tool *tool);

/* expander_tool_utils.c */
t_expand_tool	*init_expand_tool(void);
void			clear_expand_tool(t_expand_tool *tool);
void			free_expand_tool(t_expand_tool *expand_tool);

/* set_env.c */
void			set_env(t_data *data, char **env);

/* set_env_utils.c */
int				add_default_expands_to_env(t_data *data);

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

/* set_cmd_tab */
int				set_cmd_tab(char **words, int i, t_cmd_node *cmd, t_p_tool *tool);

/* set_expand_declarations */
int				set_expand_declarations(t_data *data, int i, t_cmd_node *cmd, t_p_tool *tool);

/* parser_utils.c */
t_cmd_node		*init_cmd_node(void);
char			*unmute_word(char *str);
void			print_ambiguous_redirection(char *expand);
t_p_tool		*init_p_tool(void);
int				is_path_to_cmd(char *word);
char			unmute_char(char c);

/* create_heredocs.c */
int				create_heredocs(char **words, int i, t_cmd_node *cmd, t_p_tool *tool);

/* heredoc_utils */
void			free_heredoc_tool(t_heredoc_tool *tool);
t_heredoc_tool	*init_heredoc_tool(char *lim);
char			*get_heredoc_name(int i);
int				add_path_to_heredoc_list(t_cmd_node *cmd, char *heredoc_path);
int				is_expand_declaration(char *word);

/* check_redir_op_err.c */
int 			check_redir_op_err(char **words, int i);

/* set_all_cmd_path.c */
void			set_all_cmd_path(t_data *data, t_p_tool *tool);

/*----------------------------------------------UTILS */
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

/* unmute_utils.c */
char			unmute_char(char c);
int				unmute_word_len(char *str);
char			*unmute_word(char *str);

/* ---------------------------------------------HANDLE_FREES */
/* handle_free.c */
void			global_free(t_data *data, int err);
void			free_line_datas(t_data *data);

/* handle_dels */
void			del_one_expand(void *content);
void			del_cmd(void *cmd);
void			del_unfound_expand(void *expand);
void			del_expand(void *expand);

/*----------------------------------------------BUILT_INS */

/* builtins_utils.c */
bool			is_valid_expand_key(char *key);

/* ft_echo.c */
int				ft_echo(t_data *data, char **args);

/* ft_env.c */
int				ft_env(t_data *data, char **args);

/* ft_export.c */
int				ft_export(t_data *data, char **args);

/* ft_unset.c */

int				ft_cd(t_data *data, char **args);
int				ft_unset(t_data *data, char **args);/* ft_cd.c */
/* ft_pwd.c */
int				ft_pwd(t_data *data, char **args);
int				set_path(t_data *data, char **path);

/* ft_exit */
int				ft_exit(t_data *data, char **args);

/*----------------------------------------------EXECUTER */

/* executer.c */
void			executer(t_data *data);

/* exec_children.c */
void			exec_children(t_data *data, t_list *cmd, t_exec_tool *tool);

/* open_and_set_fds */
int				open_and_set_fds(char **words, int i, t_cmd_node *cmd);

/* open_one_file.c */
int				open_and_set_fd_heredoc(t_cmd_node *cmd);
int				open_and_set_fd_in(t_cmd_node *cmd, char *infile);
int				open_and_set_fd_out(t_cmd_node *cmd, char *outfile, int flag);

/* handle_redirections.c */
void			redirect_pipe_out(t_data *data, int *pipe_fd);
void			chevron_redirection(t_data *data, t_cmd_node *cmd, t_exec_tool *tool);

/* executer_utils.c */
int				*init_pipe(t_data *data);
char			**get_env_tab(t_data *data);
int				is_last_cmd(t_list *cmd);

/* executer_tool_utils.c */
void			free_exec_tool(t_exec_tool **tool);
t_exec_tool		*init_exec_tool(t_list *cmd);

/* exec_builtins.c */
int				exec_builtins(t_data *data, char **cmd_tab, bool exit);
int				is_builtin(char *arg);

/*----------------------------------------------HANDLE SIGNALS */

/* handle_signals.c */
void	create_parent_signals(void);
void	create_child_signals(void);
void	handle_parent_sigint(int signum);
void	handle_child_sigint(int signum);
void	create_heredoc_signals(void);
void	cancel_parent_signals(void);

#endif
