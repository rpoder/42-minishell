# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:38:32 by rpoder            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/08/30 17:59:06 by rpoder           ###   ########.fr        #
=======
#    Updated: 2022/08/31 11:53:46 by mpourrey         ###   ########.fr        #
>>>>>>> a640ddebe21a9d9ab5b3edf86279058f12407ffc
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
						set_env.c \
						handle_frees/handle_frees.c \
						add_expand.c \
						syntax_checker/syntax_checker.c \
						built-ins/ft_env.c \
						handle_mutes/handle_mutes_in_quotes.c \
						expander/expander.c \
						expander/expander_utils.c \
						expander/expander_utils_2.c \
						handle_mutes/handle_mutes_in_expand.c \
						handle_mutes/mutes_in_expand_utils.c \
						lexer/lexer.c \
<<<<<<< HEAD
						lexer/split_tokens.c \
						lexer/split_tokens_utils.c \
						lexer/token_getters.c \
						lexer/token_skippers.c \
						lexer/token_trim.c \
						built-ins/ft_echo.c \
=======
						lexer/lexer_utils.c \
						lexer/word_getters_1.c \
						lexer/word_getters_2.c \
						lexer/word_skippers.c \
						lexer/word_trimmer.c \
													
#						built-ins/ft_echo.c \
>>>>>>> a640ddebe21a9d9ab5b3edf86279058f12407ffc
						built-ins/ft_export.c \
						built-ins/ft_unset.c \
						built-ins/ft_pwd.c \
						built-ins/ft_cd.c \
						built-ins/builtins_utils.c \

CC					:=	cc

RM					:=	rm

#CCFLAGS				:=	-Wall -Wextra -Werror

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

fclean				:	clean
	$(RM) -f $(PROGNAME) $(DEBUGNAME)

re					:	fclean $(NAME)

.PHONY				:	all clean fclean re
