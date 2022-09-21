# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:38:32 by rpoder            #+#    #+#              #
#    Updated: 2022/09/21 17:54:32 by rpoder           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME			:=	minishell

LIBFT				:=	./libft/libft.a

INCLUDEDIR			:=	./includes

SRCDIR				:=	./src

OBJDIR				:=	./obj

SRCS				:=	main.c \
						init.c \
						utils/utils.c\
						utils/gnl_minishell.c \
						utils/gnl_minishell_utils.c \
						utils/unmute_utils.c \
						set_env.c \
						set_env_utils.c \
						handle_frees/handle_frees.c \
						handle_frees/handle_dels.c \
						handle_expand.c \
						syntax_checker/quote_syntax_checker.c \
						syntax_checker/redirection_syntax_checker.c \
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
						built-ins/ft_unset.c \
						built-ins/ft_pwd.c \
						built-ins/ft_cd.c \
						built-ins/ft_exit.c \
						built-ins/builtins_utils.c \
						parser/parser.c \
						parser/set_cmd_tab.c \
						parser/set_expand_declarations.c \
						parser/parser_utils.c \
						parser/heredoc_utils.c \
						parser/set_all_cmd_path.c \
						executer/executer.c \
						executer/open_and_set_fds.c \
						executer/open_one_file.c \
						executer/handle_redirections.c \
						executer/executer_utils.c \
						executer/executer_tool_utils.c \
						executer/exec_builtins.c \
						handle_signals/handle_signals.c \

CC					:=	cc

RM					:=	rm

#CCFLAGS				:=	-Wall -Wextra -Werror

NAME				:=	$(PROGNAME)

OUTDIR				:=	$(OBJDIR)

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CCFLAGS) -ggdb3 -I $(INCLUDEDIR) $(addprefix -I ,$(dir $(LIBFT))) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(SRCS:.c=.o)) $(LIBFT) $(MLX)
	$(CC) $(CCFLAGS) $(addprefix $(OUTDIR)/,$(SRCS:.c=.o)) $(LIBFT) -ggdb3 -lreadline -o $(NAME)

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

fclean				:	clean
	$(RM) -f $(PROGNAME) $(DEBUGNAME)

re					:	fclean
					make $(NAME)

.PHONY				:	all clean fclean re
