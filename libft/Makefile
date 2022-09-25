# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 17:12:53 by mpourrey          #+#    #+#              #
#    Updated: 2022/09/25 15:01:42 by mpourrey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
DEL			= /bin/rm -rf
NAME		= libft.a
HEADER		= libft.h
OBJ_PATH	= ./obj

SRC = ft_atoi.c ft_atoli.c \
	ft_bzero.c ft_calloc.c \
	ft_free_tab.c ft_free_int_tab.c \
	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isinset.c ft_isprint.c ft_isint.c \
	ft_islonglongint.c \
	ft_itoa.c \
	ft_lintlen.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_ptrdup.c ft_tablen.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_clear_tab.c ft_clear_int_tab.c \
	ft_sort_tab.c  \
	ft_split.c \
	ft_str_isdigit.c ft_str_isprint.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strndup.c ft_strnstr.c \
	ft_strrchr.c ft_strrncmp.c ft_strsjoin.c ft_strtrim.c ft_substr.c \
	ft_tab_isdbl.c ft_tab_issorted.c \
    ft_tolower.c ft_toupper.c \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstlen.c \
	ft_printf.c printf_handle_write.c printf_utils.c \
	ft_printf_fd.c printf_fd_handle_write.c printf_fd_utils.c \
	ft_alloc_and_fill.c \

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_PATH)/%.o : %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

clean :
	$(DEL) $(OBJ)
	$(DEL) $(OBJ_PATH)

fclean : clean
	$(DEL) $(NAME)

re : fclean all

.PHONY : all clean fclean re
