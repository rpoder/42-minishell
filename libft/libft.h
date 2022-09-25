/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:32:48 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 20:03:10 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# define BUFFER_SIZE 50

int		ft_atoi(char *str);
long	ft_atoli(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_free_tab(char ***ptr);
void	ft_free_int_tab(int ***tab, int size);
void	ft_clear_tab(char ***tab, int size);
void	ft_clear_int_tab(int ***tab, int size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_char_isinset(char c, char *set);
int		ft_isprint(int c);
char	*ft_itoa(int c);
int		ft_lintlen(long int nb);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_ptrdup(char **ptr);
int		ft_tablen(char **ptr);
int		ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *str, int fd);
long	*ft_sort_tab(long int *tab, int len);
char	**ft_split(char const *s, char c);
int		ft_str_isdigit(char *str);
int		ft_str_isprint(char *str);
int		ft_strchr(char *str, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strndup(char *str, int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_strrncmp(char *s1, char *s2, int n);
char	*ft_strsjoin(int nb_arg, ...);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, int start, int len);
int		ft_tab_isdbl(long int *tab, int len);
int		ft_tab_issorted(long int *tab, int len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_alloc_and_fill(char *str);
int		ft_isint(long int num);
int		ft_islonglongint(long int num);

/* LIST */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **alst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
int		ft_lstlen(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);

/* PRINTF */
int		ft_printf(const char *s, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putaddress(unsigned long int n);
int		ft_putint(int n);
int		ft_putunint(unsigned int n, char *base);
int		ft_strlen_printf(char *str);
int		ft_reslen_uli(unsigned long int n, int base_len);
int		ft_itoabase_uli(unsigned long int n, char *base);
int		ft_itoabase_ui(unsigned int n, char *base);
int		ft_reslen_ui(unsigned int n, int base_len);

/* PRINTF_FD */
int		ft_printf_fd(const char *s, int fd, ...);
int		ft_putaddress_fd(unsigned long int n, int fd);
int		ft_putint_fd(int n, int fd);
int		ft_putunint_fd(unsigned int n, char *base, int fd);
int		ft_itoabase_uli_fd(unsigned long int n, char *base, int fd);
int		ft_itoabase_ui_fd(unsigned int n, char *base, int fd);

#endif
