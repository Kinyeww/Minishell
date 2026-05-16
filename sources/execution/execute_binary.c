/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/05/16 19:46:10 by syee             ###   ########.fr       */
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

// when no / in command
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


char *get_path(char *arg, char *envp_path)
{
	char	*path;
	char	*program_name;
	char	**envp_path_arr;
	int		i;

	//printf("debug in get_path : path = %s\n", envp_path);
	
	/*
	if its already an absolue path to the program 
	or
	if the envp_path is unset
	*/
	if (ft_strchr(arg, '/') != 0)
		return (ft_strdup(arg));
	
	program_name = ft_strjoin("/", arg);
	if (!envp_path)
		return (program_name);
	envp_path_arr = ft_split(envp_path, ':');
	
	
	//======== debugging ft_split =====
	// printf("debug : ft_split : path \n");
	// i = 0;
	// while (envp_path_arr[i] != NULL)
	// {
	// 	printf ("%s\n", envp_path_arr[i]);
	// 	i++;
	// }
	
	
	//printf("\ndebug path after strjoin: %s\n", program_name);
	i = 0;
	while (envp_path_arr[i] != NULL)
	{
		path = ft_strjoin(envp_path_arr[i], program_name);
		
		if (access(path, X_OK) == 0)
		{
			//printf ("full path name result %s\n", path);
			free (program_name);
			break ;
		}
		free (path);
		i++;
	}
	//=====freeeing the ft_split list======
	i = 0;
	while (envp_path_arr[i] != NULL)
	{
		free(envp_path_arr[i]);
		i++;
	}
	free(envp_path_arr);
	
	return (path);

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

/*

Steps in binary 
1. get the $PATH from envp
2. get the path of the program (/program or ls) with get_path()
3. check if there are any arguments for the path , if yes assifn exceve_argv
4. create an envp_arr using create_envp_arr() to be passed into exceve 
5. run exceve using values from 2.program path , 3. exceve_argv , 4. envp_arr 
6. check for error and print err_msg accordingly 
7. before return(), free all the values

*/

int binary(char **argv, t_data *data)
{
	char **envp_arr;
	char **execve_argv;
	char *path_name;
	char *envp_path;
	
	//======get PATH and store into str=======
	envp_path = get_key_value("PATH", data->envp_list);
	//	printf("debug : path = %s\n", envp_path);

	//====== get the path of the program =======
	path_name = get_path(argv[0], envp_path);
	//printf("path name : %s\n", path_name);
	
	//====== check if there are arguments for the program =======
	if (argv[1] != NULL)
		execve_argv = argv + 1;
	else 
		execve_argv = argv ; //to nullify werning
		
	//for (int i = 0; execve_argv[i] != NULL ; i++)
	//	printf("execve arguments : %s\n", execve_argv[i]);
		
	//====== creating envp arr to pass into exceve =======
	envp_arr = create_envp_arr(data->envp_list);
	
	//=======run exceve=======
	
	//when PATH is unset, the path_name will just be the strdup of the name 
	if (execve(path_name, argv, envp_arr) == -1)
	{
		if (ft_strchr(path_name, '/'))
			execve_fail(argv[0]);
		else
			path_fail(argv[0]);
	}

	//======free up=======
	free(path_name);
	free(envp_path);
	free_envp_arr(envp_arr);
	return (0); //based on the code within 
}

