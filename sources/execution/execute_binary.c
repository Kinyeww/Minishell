/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/05/16 22:07:21 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <error.h>

#include <errno.h>
// when with / in command
void	execve_fail(char *file_dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}

// when no / in command, no such file or directory 
void	path_fail(char *file_dir)
{
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
/*
my code issues : inconsistent return types 
*/
void free_str_arr(char **str_arr)
{
	int i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

//check the freeing here, after revamping to return NULL on failure some stuff are not freed properly
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
		{
			free (program_name);
			break ;
		}
		free (return_path);
		return_path = NULL;
		i++;
	}
	free (program_name);
	free_str_arr(envp_path_arr);
	return (return_path);
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
	char *envp_path;
	
	//======get PATH and store into str=======
	envp_path = get_key_value("PATH", data->envp_list);
	//	printf("debug : path = %s\n", envp_path);

	//====== get the path of the program =======
	path_name = get_path(argv[0], envp_path);
	//printf("path name : %s\n", path_name);
	
	if (!path_name)
	{
		errno = ENOENT;
		path_fail(argv[0]);
		return (127);
	}
		
	//====== creating envp arr to pass into execve =======
	envp_arr = create_envp_arr(data->envp_list);
	
	//=======run exceve=======
	execve(path_name, argv, envp_arr);
	execve_fail(argv[0]);

	//======free up=======
	free(path_name);
	free(envp_path);
	free_envp_arr(envp_arr);
	return (126); //based on the code within 
}

/*
just check the error codes 
*/