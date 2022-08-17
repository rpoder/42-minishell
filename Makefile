# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:38:32 by rpoder            #+#    #+#              #
#    Updated: 2022/08/17 21:54:47 by mpourrey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGNAME			:=	minishell

LIBFT				:=	./libft/libft.a

INCLUDEDIR			:=	./includes

SRCDIR				:=	./src

OBJDIR				:=	./obj

SRCS				:=	main.c \
						init.c \
						utils/utils.c utils/utils_2.c\
						set_env.c \
						syntax_checker/syntax_checker.c \
						metachar_interpreter/metachar_interpreter.c \
						metachar_interpreter/set_prompt_line_utils.c \
						metachar_interpreter/set_prompt_line_utils_2.c \
						lexer/lexer.c \
						lexer/split_tokens.c \
						lexer/split_tokens_utils.c \
						lexer/token_getters.c \
						lexer/token_skippers.c \
						handle_frees/handle_frees.c \
						built-ins/ft_echo.c \
						built-ins/ft_env.c \
						built-ins/ft_export.c \

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

norm				:
	norminette ./libftprintf ./src ./includes

push				:
	$(MAKE) fclean
	git add *
	git status
	git commit -m "$m"
	git push origin master

.PHONY				:	all clean fclean re norm test push
