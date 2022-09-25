/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 20:03:30 by mpourrey         ###   ########.fr       */
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
# include <sys/ioctl.h>

extern bool		g_close_heredoc;

# define PATH_MAX 4096
# define ENV_DFL_PATH_1 "/mnt/nfs/homes/rpoder/bin:/usr/local/sbin:"
# define ENV_DFL_PATH_2 "/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:"
# define ENV_DFL_PATH_3 "/usr/games:/usr/local/games:/snap/bin"

# define FD_UNDEFINED -2

enum	e_errors {
	malloc_err = -100,
	open_err,
	parsing_err,
	err_not_defined,
	no_err,
	pipe_err,
	dup_err,
	waitpid_err,
	close_err,
	path_max_err,
	fork_err,
	ctrl_c,
	end
};
enum	e_builtins {
	e_cd = 1,
	e_echo,
	e_env,
	e_exit,
	e_export,
	e_pwd,
	e_unset
};

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
	char	**default_env;
}	t_data;

typedef struct s_cmd_node {
	char	*path;
	char	**cmd_tab;
	int		fd_in;
	int		fd_out;
	t_list	*heredocs;
}	t_cmd_node;

/*---------------------------------------------- INIT */
/* init_data.c */
t_data			*init_data(char **env);

/* set_env.c */
void			set_env(t_data *data, char **env);
char			*get_env_value(char *str);
char			*get_env_key(char *str);

/* set_env_utils.c */
int				add_default_expands_to_env(t_data *data);
int				add_default_shlvl(t_data *data);

/*---------------------------------------------- SYNTAX CHECKER */
/* quote_syntax_checker */
int				quote_syntax_checker(char *str);
/* redir_op_syntax_error.c */
void			redirection_syntax_printer(char **words);
int				check_redir_op_error(char **words);

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
int				is_limiter(char *str, int i);

/* expander_tool_utils.c */
t_expand_tool	*init_expand_tool(void);
void			clear_expand_tool(t_expand_tool *tool);
void			free_expand_tool(t_expand_tool *expand_tool);

/*---------------------------------------------- HANDLE_MUTES */
/* handle_mutes_in_expand.c */
char			*get_muted_expand_value(char *value);

/* mutes_in_expand_utils.c */
t_mute_tool		*init_mute_tool(void);
void			set_mute_tool(t_mute_tool *tool, char *src);
void			clear_mute_tool(t_mute_tool *tool);
int				skip_if_space(char *value, int i);

/* handle_mutes_in_quotes.c */
void			mute_in_quotes(t_data *data);

/*---------------------------------------------- LEXER */
/*lexer.c*/
void			lexer(t_data *data);

/* lexer_utils.c */
t_split_tool	*init_split_tool(void);
void			set_tool_for_next_word(t_split_tool *split_tool, int i);
int				redirection_word_len(char *str, int i);
int				skip_node(char **words, int len);

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

/* word_trimmer.c */
char			*word_trim(char *src);

/*----------------------------------------------PARSER*/
/* parser.c */
int				parser(t_data *data);

/* check_redir_op_err.c */
int				check_redir_op_err(char **words, int i);

/* set_cmd_tab */
int				set_cmd_tab(char **words, int i, t_cmd_node *cmd,
					t_p_tool *tool);

/* set_all_cmd_path.c */
void			set_all_cmd_path(t_data *data, t_p_tool *tool);

/* create_heredocs.c */
int				create_heredocs(char **words, int i, t_cmd_node *cmd,
					t_p_tool *tool);

/* heredoc_utils */
t_heredoc_tool	*init_heredoc_tool(char *lim);
void			free_heredoc_tool(t_heredoc_tool *tool);
char			*get_heredoc_name(int i);
int				add_path_to_heredoc_list(t_cmd_node *cmd, char *heredoc_path);

/* set_expand_declaration */
int				set_expand_declaration(t_data *data, char *declaration);

/* parser_utils.c */
t_cmd_node		*init_cmd_node(void);
t_p_tool		*init_p_tool(void);
int				is_path_to_cmd(char *word);
int				is_expand_declaration(char *word);
int				is_valid_expand_declaration(char **words);

/*----------------------------------------------EXECUTER */
/* executer.c */
void			executer(t_data *data);

/* exec_children.c */
void			exec_children(t_data *data, t_list *cmd, t_exec_tool *tool);

/* exec_children_utils.c */
void			handle_pipe(t_data *data, t_exec_tool *tool);
void			handle_fork(t_data *data, t_exec_tool *tool);
void			redirect_to_pipe(t_data *data, t_exec_tool *tool);

/* exec_builtins.c */
int				exec_builtins(t_data *data, char **cmd_tab, bool is_child,
					t_exec_tool *tool);
int				is_builtin(char *arg);

/* exec_no_child_builtin.c */
void			exec_no_child_builtin(t_data *data, t_list *cmd,
					t_exec_tool *tool);

/* open_and_set_fds */
int				open_and_set_fds(char **words, int i, t_cmd_node *cmd);

/* open_one_file.c */
int				open_and_set_fd_heredoc(t_cmd_node *cmd);
int				open_and_set_fd_in(t_cmd_node *cmd, char *infile);
int				open_and_set_fd_out(t_cmd_node *cmd, char *outfile, int flag);

/* handle_redirections.c */
void			chevron_redirection(t_data *data, t_cmd_node *cmd,
					t_exec_tool *tool);
void			out_chevron_redir(t_data *data, t_cmd_node *cmd,
					t_exec_tool *tool);
void			redirect_pipe_out(t_data *data, int *pipe_fd);

/* executer_utils.c */
int				*init_pipe(t_data *data);
int				is_redir_err_or_chevron_err(t_data *data);
int				is_last_cmd(t_list *cmd);
char			**get_env_tab(t_data *data);
void			free_exec_children(t_data *data, t_exec_tool *tool,
					char **env_tab);

/* executer_tool_utils.c */
t_exec_tool		*init_exec_tool(t_list *cmd);

/* executer_tool_utils_2.c */
void			free_exec_tool(t_exec_tool **tool);

/*----------------------------------------------BUILT_INS */
/* ft_echo.c */
int				ft_echo(t_data *data, char **args);

/* ft_cd.c */
int				ft_cd(t_data *data, char **args);

/* ft_env.c */
int				ft_env(t_data *data, char **args);

/* ft_export.c */
int				ft_export(t_data *data, char **args);

/* ft_export_utils.c */
char			*trim_and_alloc_value(char *str);
char			*trim_and_alloc_key(char *str);
int				set_trim_alloc_keyvalue(char *arg, char **key, char **value);

/* ft_unset.c */
int				ft_unset(t_data *data, char **args);

/* ft_pwd.c */
int				ft_pwd(t_data *data, char **args);
int				set_path(t_data *data, char **path);

/* ft_exit */
int				ft_exit(t_data *data, char **args, t_exec_tool *tool);

/* builtins_utils.c */
bool			is_valid_expand_key(char *key);

/*----------------------------------------------HANDLE SIGNALS */
/* handle_signals.c */
void			cancel_sigquit(void);
void			custom_all_sigs(void);
void			default_all_sigs(void);
void			ignore_all_sigs(void);
void			init_heredoc_sig(void);

/*----------------------------------------------UTILS */
/* utils.c */
int				is_word_separator(char c);
int				is_redirection_operator(char c);
int				is_space(char c);
int				is_pipe(char c);
int				is_valid_line(char *str);

/* init_quotes */
void			set_quotes(char c, t_quotes *quotes);
void			clear_quotes(t_quotes *quotes);
t_quotes		*init_quotes(void);

/* unmute_utils.c */
char			unmute_char(char c);
int				unmute_word_len(char *str);
char			*unmute_word(char *str);

/* handle_expand.c */
void			add_expand(t_data *data, t_list **alst, char *key, char *value);
int				set_expand(t_data *data, char *key, char *new_value);
bool			set_on(t_list **alst, char *key, char *new_value);

/* handle_malloced_expand.c */
int				set_malloced_expand(t_data *data, char *key,
					char *new_value);
int				set_malloced_value_expand(t_data *data, char *key,
					char *new_value);

/* ---------------------------------------------HANDLE_FREES */
/* handle_free.c */
void			global_free(t_data *data, int err);
void			free_line_datas(t_data *data);

/* handle_dels */
void			del_cmd(void *cmd);
void			del_unfound_expand(void *expand);
void			del_expand(void *expand);

#endif
