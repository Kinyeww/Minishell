#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == APPEND
		|| type == HEREDOC);
}

// char	*ft_strdup(char *src)
// {
// 	size_t	i;
// 	char	*s1cpy;

// 	i = 0;
// 	while (src[i] != '\0')
// 		i++;
// 	s1cpy = malloc(sizeof(char) * (i + 1));
// 	if (!s1cpy)
// 		return (NULL);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		s1cpy[i] = src[i];
// 		i++;
// 	}
// 	s1cpy[i] = '\0';
// 	return (s1cpy);
// }
