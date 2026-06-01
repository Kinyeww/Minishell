/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 07:24:28 by syee              #+#    #+#             */
/*   Updated: 2026/05/29 07:25:58 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_binary(char *file_dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}

char	*get_key_value(char *key, t_env *envp_list)
{
	t_env *current;

	current = envp_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

void free_str_arr(char **str_arr)
{
	int i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

char *strjoin_envp(char *key, char *value)
{
	char	*joined_str;
	int		keylen;
	int		valuelen;

	keylen = ft_strlen(key);
	valuelen = ft_strlen(value);
	joined_str = malloc(keylen + valuelen + 2);
	memcpy(joined_str, key, keylen);
	memcpy(joined_str + keylen , "=", 1);
	memcpy(joined_str + keylen + 1, value, valuelen);
	joined_str [keylen + valuelen + 1] = '\0';
	return (joined_str);
}

char **create_envp_arr(t_env *envp_list)
{
	char	**envp_arr;
	t_env	*current;
	char	*joined;
	int		i;

	current = envp_list;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	envp_arr = malloc((sizeof(char *) * (i + 1)));
	current = envp_list;
	i = 0;
	while (current)
	{
		joined = strjoin_envp(current->key, current->value);
		envp_arr[i++] = joined;
		current = current->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}
