/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertrmar <bertrmar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:27:36 by bertrmar          #+#    #+#             */
/*   Updated: 2025/06/27 10:46:44 by bertrmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_list
{
	int				number;
	struct s_list	*next;
}	t_list;

typedef struct s_split_exept
{
	int		wait;
	char	exept;
	char	**new;
	int		start;
	int		end;
	int		alloc;
}	t_split;

int				ft_abs(int num);
int				ft_atoi(const char *str);
int				ft_atol(char *str, long *result);
void			ft_bzero(void *str, size_t n);
void			*ft_calloc(size_t number, size_t size);
char			*ft_strcat(const char *s1, const char *s2);
int				ft_check_base(char *base);
void			ft_free_split(char **str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
char			*ft_ltoa(long n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst);
void			ft_lstdelone(t_list *lst);
void			ft_lstiter(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(int number);
int				ft_lstsize(t_list *lst);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *str, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_base(int nbr, char *base);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr_unsigned(unsigned int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split_chr(char *s, char *c, char exept);
char			**ft_split(char const *s, char *c);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_var(int nbr_str, ...);
unsigned int	ft_strlcat(char *dest, const char *src, size_t size);
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*get_next_line(int fd);

#endif
