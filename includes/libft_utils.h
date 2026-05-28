#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include "minishell.h"
// #include "../../includes/minishell.h"
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
char	*ft_strdup(char *string);
char	*ft_strchr(char *string, char c);
char	*ft_strndup(char *string , int size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_substr(char *s, int start, int len);
int		ft_strncmp(char *s1, char *s2, size_t n);

#endif