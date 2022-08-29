/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:07:56 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 18:49:39 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_int_len(int n);
int		ft_uint_len_base(unsigned int n, int base);
int		ft_lstsize(t_list *lst);
int		ft_atoi(const char *nptr);
int		ft_atof(const char *s, float *n);
int		ft_atoi_err(const char *s, int *n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_bzero(void *s, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char	*big, const char *little, size_t len);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(char *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lst_at(t_list *begin_list, unsigned int nbr);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**			CUSTOM			**/

//gnl

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_leftover
{
	char	str[BUFFER_SIZE];
	size_t	size;
}	t_leftover;

char	*ft_gnl(int fd);

//printf
# define WRITE_BUFFER 65536

typedef struct s_format
{
	char	convertion;
	char	alternate;
	char	left;
	char	padd_char;
	int		padd_size;
	int		has_precision;
	int		precision;
	char	sign;
}	t_format;

//Core
int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_printf_buffer(int fd, const char *str, int size);

//Format
int		set_format(t_format *format, const char *str, int *index);
int		__padding(t_format *format, const char *str);
int		__padding_printf(int fd, int *size, int len, t_format *format);
int		__precision(t_format *format, const char *str);
int		__precision_len(int len, t_format *format);
int		__precision_printf(int fd, t_format *format);

//Convertion
int		ft_printf_char(int fd, char c, t_format *format);
int		ft_printf_str(int fd, char *str, t_format *format);
int		ft_printf_int(int fd, int n, t_format *format);
int		ft_printf_uint(int fd, unsigned int u, t_format *format);
int		ft_printf_ptr(int fd, void *ptr, t_format *format);
int		ft_printf_lowhex(int fd, unsigned int nbr, t_format *format);
int		ft_printf_uphex(int fd, unsigned int nbr, t_format *format);

int		__uint_printf(int fd, unsigned int n);

//min
char	minc(char a, char b);
int		min(int a, int b);
long 	minl(long a, long b);
float	minf(float a, float b);
double	mind(double a, double b);

#endif
