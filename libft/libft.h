/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 20:35:40 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 14:52:46 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_list
{
	long			content;
	int				flag;
	struct s_list	*next;
}	t_list;

int		ft_printf(const char *format, ...);
int		write_int(int i);
void	write_uint(unsigned int n, int *count);
int		write_char(char c);
int		write_str(char *str);
int		num_len(int n);
void	put_hex(unsigned int n, int *count, char c);
int		put_pointer(void *pointer, int *count);
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
long	ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t size);
char	*ft_strncat(char *dest, const char *src, unsigned int nb);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
int		ft_memcmp(const void *sp1, const void *sp2, size_t n);
t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new_lst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_free2d(char *strs);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strndup(const char *s1, size_t n);
void	ft_new_node(t_list **list, int content);
void	ft_freev(void **ptr, int len, bool free_seg);
void	free2d_array(void **arry);

#endif
