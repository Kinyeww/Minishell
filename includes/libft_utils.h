#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

#include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
char	*ft_strdup(char *string);
char	*ft_strchr(char *string, char c);
char	*ft_strndup(char *string , int size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
long	ft_atol(char *str);

#endif