/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/05/15 20:24:26 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <error.h>
/*
functions used :

strerror (errno)
int access (pathname, code/mode)
	: if -1 failure, 0 is success
int execve (pathname, argv_to_pass_to_program[], envp[])
	: if -1 is returned, then errno is set

codes :
under #include <unistd.h>

R_OK : read ok ?
W_OK : write ok
X_OK : execute ok?
F_OK : exists ?

should i test in get_path or in binary

*/
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
if the passed argument has "/", it is either the absolute or
	 relative path to the program, then can be run directly
if the passed arugment is "program" , has to be checked againts PATH


argv[0] is passed to get_path

*/

char *get_path(char *arg, char *envp_path)
{
	char	*path;
	char	*string;
	char	**path_arr;

	path_arr = ft_split(envp_path, ':');
	if (ft_strchr(arg, '/') == 0)
		path = ft_strdup(arg);
	else
	{
		path = ft_strjoin("/", arg);
		while (path_arr)
		/*
			caution ;
			/pyenv/plugins, i cant pass in "pyen" , it will show that there is a
				match, but it's just the string that match not the correct executable
			do i extract the entire list : by : then run ?

		idea:
		- store the paths delimited by : into an array using ft_split 
		- get the last / of the list (via strrnchr)
			from the "/0" of the path till the last /
			----------- or --------
		- ft_strjoin ("/", cmd), and do ft_strnstr
		
		while (arr_not_end)
		{
			ptr of last / = via ft_strrnchr (arr[i]);
			if (ft_strcmp(ptr_from_last_/ , string) == 0)
				return (arr[i])
			arr++;
		}
		if does not match , return NULL;
		*/

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
	
	//======check if it already has absolute path=======
	
		//====== get the path of the program =======
		path_name = get_path(argv[0], data);
		printf("path name : %s\n", path_name);
		//======if not=======
		
			//======if PATH gets unset=======
			/*
			//if there is no path, the retun value from get_key_value == NULL
			if (envp_path == NULL)
			{
				// minishell: x; no such file or directory
			}
			*/

	//====== creating envp arr to pass into exceve =======
	envp_arr = create_envp_arr(data->envp_list);
	
	
	//=======checking access here=======
	if (access(path_name ,F_OK | X_OK) == -1)
	{
		ft_putstr_fd("minishell: no such file", 2);

		//======= call error =======
	}
	//=======run exceve=======
		//execve(get_path, argv, e	nvp_arr);
	
	//======free up=======
	free(path_name);
	free(envp_path);
	free_envp_arr(envp_arr);
}

/*

if there is "/" then "no such file or directory" as denoted by strerror(errno)
if its just the "name of the program" then "x : command not found" as denotes by strerror(errno)

*/
#include <errno.h>

void	print_err_no_file_dir(char *file_dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}

void	print_err_no_command(char *file_dir)
{
	ft_putstr_fd(file_dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}