#include "minishell.h"
#include "libft_utils.h"
#include <stdlib.h>

char	*get_env_val(char *name, t_env *envp)
{
	int		len;
	t_env	*current;

	len = ft_strlen(name);
	current = envp;
	while (current)
	{
		if (ft_strncmp(current->key, name, len) == 0
			&& current->key[len] == '\0')
			return (current->value);
		current = current->next;
	}
	return ("");
}

int	is_var_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_var_char(str[i]))
		i++;
	return (i);
}

char	*append_char(char *result, char c)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(result);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
	{
		free (result);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new[i] = result[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(result);
	return (new);
}

char	*append_str(char *result, char *to_add)
{
	int		len1;
	int		len2;
	char	*new;
	int		i;
	int		j;

	len1 = ft_strlen(result);
	len2 = ft_strlen(to_add);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	i = 0;
	while (i < len1)
	{
		new[i] = result[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		new[i + j] = to_add[j];
		j++;
	}
	new[i + j] = '\0';
	free(result);
	return (new);
}
