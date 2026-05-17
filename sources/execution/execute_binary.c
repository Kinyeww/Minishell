/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/05/17 14:21:04 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	binary_fail(char *file_dir)
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

/*
terrible readability but done for norm purposes , its actually :

	while (envp_path_arr[i])
	{
		return_path = ft_strjoin(envp_path_arr[i], program_name);
		if (access(return_path, X_OK) == 0)
		{
			free(program_name);
			free_str_arr(envp_path_arr);
			return (return_path);
		}
		free(return_path);
		i++;
	}
	free(program_name);
	free_str_arr(envp_path_arr);
	return (NULL);
	
	if the binary doesn't exist = NULL
	if the envp_path does't exist = NULL
	
	NULL err = ENOENT
*/
char *get_path(char *arg, char *envp_path)
{
	char	*return_path;
	char	*program_name;
	char	**envp_path_arr;
	int		i;

	if (ft_strchr(arg, '/') != 0)
		return (ft_strdup(arg));
	if (!envp_path)
		return (NULL);
	program_name = ft_strjoin("/", arg);
	envp_path_arr = ft_split(envp_path, ':');
	i = 0;
	while (envp_path_arr[i] != NULL)
	{
		return_path = ft_strjoin(envp_path_arr[i], program_name);	
		if (access(return_path, X_OK) == 0)
			return (free(program_name),free_str_arr(envp_path_arr),return_path);
		free (return_path);
		i++;
	}
	free (program_name);
	free_str_arr(envp_path_arr);
	return (NULL);
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



/*
if ./programdontexist 
	runs exceve, 127
if envp_path is unset (NULL) //not tested yet
	path = NULL , exceve doesnt run , 127
if invalidprogramname (NULL) 
	runs exceve , 127
if ./nopermission
	runs exceve , 126
*/

int binary(char **argv, t_data *data)
{
	char **envp_arr;
	char *path_name;
	char *envp_path;
	
	envp_path = get_key_value("PATH", data->envp_list);
	path_name = get_path(argv[0], envp_path);
	if (!path_name)
	{
		errno = ENOENT;
		free(envp_path);
		binary_fail(argv[0]);
		return (127);
	}
	
	envp_arr = create_envp_arr(data->envp_list);
	
	execve(path_name, argv, envp_arr);
	binary_fail(argv[0]);

	free(path_name);
	free(envp_path);
	free_str_arr(envp_arr);

	if (errno == ENOENT)
		return (127);
	return (126);
}
