/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/05/14 23:43:59 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <error.h>
/*
functions used :
access (pathname, mode)
execve (pathname, argv[], envp[])

codes :
R_OK : read ok ?
W_OK : write ok
X_OK : execute ok?
F_OK : exists ?
*/
char *get_path(char *arg)
{
	char *path;

	if (strchr(arg, '/') == 0)
		path = ft_strdup(arg);
	else
	{
		//the delimiters are :
		return (arg);
	}
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

char **create_envp_arr(char **envp_list)
{
	char	**envp_arr;
	t_env	*current;
	char	*joined;
	int		i;

	*envp_list = current;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	envp_arr = malloc((sizeof(char *) * i + 1));
	current = envp_list;
	i = 0;
	while (current)
	{
		joined = strjoin_envp(current->key, current->value);
		envp_list[i++] = joined;
		current = current->next;
	}
	envp_list[i] = NULL;
}
/*

*/
void	free_envp_arr(char **envp_arr)
{
	int	i;

	i = 0;
	while (envp_arr[i] != NULL)
		free(envp_arr[i++]);
	free(envp_arr);
}
int binary(char **argv, t_data *data)
{
	char **envp_arr;
	char *path_name;
	
	path_name = get_path(argv[0]);
		
	envp_arr = create_envp_arr(data->envp_list);
	
	printf ("%s\n", envp_arr);
	//execve(get_path, argv, envp_arr);
	free_envp_arr(envp_arr);
}