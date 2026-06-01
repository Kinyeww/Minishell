/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:43:17 by syee              #+#    #+#             */
/*   Updated: 2026/06/01 14:18:05 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

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

	if (!arg || arg[0] == '\0')
		return (NULL);
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

/*
exit 0: Indicates success. This is the default if no number is given.
exit 1: Indicates a generic error
exit 2: Misuse of shell built-ins or incorrect arguments.
exit 127: Command not found

*/

/*
based on chiang's reccomendation 
: might as well just run execve while testing ;
rather than using access to check the state of the file
*/

/*
this code can be optimized but idk how 
should be considered when doint the error code 
*/
int execute_binary(char **argv, t_data *data)
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
		print_err_binary(argv[0]);
		return (127);
	}
	
	envp_arr = create_envp_arr(data->envp_list);
	
	execve(path_name, argv, envp_arr);
	print_err_binary(argv[0]);

	free(path_name);
	free(envp_path);
	free_str_arr(envp_arr);

	if (errno == ENOENT)
		return (127);
	return (126);
}
