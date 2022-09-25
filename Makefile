# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:38:32 by rpoder            #+#    #+#              #
#    Updated: 2022/09/26 01:08:09 by mpourrey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME			:=	minishell

LIBFT				:=	./libft/libft.a

INCLUDEDIR			:=	./includes

SRCDIR				:=	./src

OBJDIR				:=	./obj

SRCS				:=	main.c \
						init/init_data.c \
						init/set_env.c \
						init/set_env_utils.c \
						utils/init_quotes.c \
						utils/utils.c \
						utils/unmute_utils.c \
						utils/handle_expand.c \
						utils/handle_malloced_expand.c \
						handle_frees/handle_frees.c \
						handle_frees/handle_dels.c \
						syntax_checker/quote_syntax_checker.c \
						syntax_checker/redirection_syntax_printer.c \
						built-ins/ft_env.c \
						handle_mutes/handle_mutes_in_quotes.c \
						expander/expander.c \
						expander/expand_getters.c \
						expander/expand_lens.c \
						expander/expander_utils.c \
						expander/expander_tools_utils.c \
						handle_mutes/handle_mutes_in_expand.c \
						handle_mutes/mutes_in_expand_utils.c \
						lexer/lexer.c \
						lexer/lexer_utils.c \
						lexer/word_getters_1.c \
						lexer/word_getters_2.c \
						lexer/word_skippers.c \
						lexer/word_trimmer.c \
						built-ins/ft_echo.c \
						built-ins/ft_export.c \
						built-ins/ft_export_utils.c \
						built-ins/ft_unset.c \
						built-ins/ft_pwd.c \
						built-ins/ft_cd.c \
						built-ins/ft_exit.c \
						built-ins/builtins_utils.c \
						parser/parser.c \
						parser/set_cmd_tab.c \
						parser/set_expand_declaration.c \
						parser/parser_utils.c \
						parser/create_heredocs.c \
						parser/heredoc_utils.c \
						parser/check_redir_op_err.c \
						parser/set_all_cmd_path.c \
						executer/executer.c \
						executer/exec_builtins.c \
						executer/exec_children.c \
						executer/exec_children_utils.c \
						executer/exec_no_child_builtin.c \
						executer/open_and_set_fds.c \
						executer/open_one_file.c \
						executer/handle_redirections.c \
						executer/executer_utils.c \
						executer/executer_tool_utils.c \
						executer/executer_tool_utils_2.c \
						handle_signals/sig_prototypes.c \
						handle_signals/sig_prototypes2.c \
						handle_signals/sig_handler.c \

CC					:=	cc

RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror

NAME				:=	$(PROGNAME)

OUTDIR				:=	$(OBJDIR)

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) -I $(INCLUDEDIR) $(addprefix -I ,$(dir $(LIBFT))) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(SRCS:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(addprefix $(OUTDIR)/,$(SRCS:.c=.o)) $(LIBFT) -lreadline -o $(NAME)

all					:	$(NAME)

ifdef LIBFT
$(LIBFT)			:
	$(MAKE) -C $(dir $(LIBFT)) all
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
ifdef LIBFT
	$(MAKE) -C $(dir $(LIBFT)) fclean
endif
	$(RM) -rf $(OBJDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME)

re					:	fclean
					make $(NAME)

.PHONY				:	all clean fclean re
