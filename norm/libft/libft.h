/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksilver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:30:49 by ksilver           #+#    #+#             */
/*   Updated: 2020/05/07 03:48:14 by ksilver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include "GNL/get_next_line.h"

typedef struct			s_list
{
	struct s_list		*next;
	void				*content;
}						t_list;

typedef struct			s_mem_list
{
	struct s_mem_list	*next;
	void				*obj;
}						t_mem_list;

void					free_gc(void *ptr);
void					*malloc_gc(int size);
void					free_all(void);
char					*ft_itoa (long long int n);
long int				ft_latoi(const char *str);
double					ft_atod(char *str);
void					*dup_cpy(void *source, void *dst, int size);
double					ft_mod_db(double num);
double					ft_pwr_db(double num, int pow);
char					*ft_uitoa(unsigned long long int n);
char					*ft_strins_fr(char *main, char *add, int adr,\
																	char mode);
char					*ft_strchr(char *s, int c);
char					*ft_strrchr(char *s, int c);
char					*ft_strdup (const char *str1);
char					**ft_split(char const *s, char c);
char					*ft_uitoa_base(unsigned int n, char *base);
char					*ft_ultoa_base(unsigned long int n, char *base);
char					*ft_ulltoa_base(unsigned long long int n, char *base);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char *s1, char const *set);
char					*ft_strnstr(char *big, const char *ltl, size_t len);
char					*ft_substr(char const *s, size_t start, size_t len);
char					*ft_strmapi(char const *s,\
												char (*f)(unsigned int, char));
int						ft_isascii(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_lstsize(t_list *lst);
int						ft_atoi(const char *str);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstnew(void *content);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void*));
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putchar_fd (char c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_bzero(void *src, size_t len);
void					*ft_calloc (size_t number, size_t size);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(void *));
void					ft_lstadd_front(t_list **lst, t_list *new);
void					*ft_memset(void *src, int sym, size_t len);
void					*ft_memchr(void *s, int c, size_t n);
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					*ft_memcpy(void *dest, const void *src, size_t len);
void					*ft_memmove(void *dest, const void *src, size_t len);
void					*ft_memccpy(const void *dest, const void *src, int ch,
								size_t len);
long long int			ft_mod(long long int num);

#endif
