/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:44:11 by syee              #+#    #+#             */
/*   Updated: 2026/05/10 06:18:50 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/minishell.h"
#include "../utils/utils.c"

#define TOO_MANY_ARG_ERR "minishell : export: 'too many arguments'\n"
#define HOME_NOT_SET "minishell :cd: HOME not set\n"

char *get_env_value(t_data *data, char *key);
int change_dir(char *path, char *old_path, t_data *data);
void update_env(t_data *data, char *key, char *value);
void print_err_cd(char *path);

/*
1. check for amount of arguments
	return if there is more then 2
save current directory to update env later
	if there is only 1 (cd) then go to home directory 
3. if there is exactly 2 (cd xx) , run the command to change directory and update env // it could be absolute or relative 
4. once done update env n(OLDPWD && PWD)
5. if error , print error 
6. return error flag to update $?

used:
getcwd
getenv
strerror, the error is stored into a global errno value 

Still need to handle ~ or - 
//check online or other references to see if it handles them being unset 9also ask cadets in campus to double confirm) 
// to solve the problem of unknown buffer can probably use PATH_MAX bur its not guaranteed this exists in the system 
// the reutrn value should be the num for $? so it can be updaated inside handle_built_ins
*/

/* 
can use #define _USE_GNU to use getcwd(NULL,0)*/
int cd(char **argv, t_data *data)
{
	int		argc;
	char	*path;
	char	old_dir[1024];

	argc = 0;
	while(argv[argc])
		argc++;
	if (argc > 2)
		return (write(2, TOO_MANY_ARG_ERR, strlen(TOO_MANY_ARG_ERR)), 1);
	if (!getcwd(old_dir, sizeof(old_dir)))
		old_dir[0] = '\0';
	if (argc == 1)
	{
		path = get_env_value(data, "HOME"); //what do i return here? a freeable value ?
		if (!path)
			return (write(2, HOME_NOT_SET, strlen(HOME_NOT_SET)), 1);
	}
	else
	{
		//if (ft_strcmp(argv[1], '-') == 0)
		//	path = get_env_value(data, "OLDPWD");
		//else if (ft_strcmp(argv[1], '~') == 0)
		//	path = get_env_value(data, "PWD");
		path = argv[1];
	}
	return (change_dir(path, old_dir, data));
}

char *get_env_value(t_data *data, char *key)
{
	t_env	*current;

	current = data->envp_list;
	while(current != NULL)
	{
		if (current->key == key)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/*
cannot be using the path inputed by the user 
*/
int change_dir(char *path, char *old_path, t_data *data)
{
	char current_path[1024];

	if (chdir(path) != 0)
		return(print_err_cd(path), 1);
	update_env(data, "OLDPWD", old_path);
	getcwd(current_path, sizeof(current_path));
	update_env(data, "PWD", current_path);
	return (0);
}

void update_env(t_data *data, char *key, char *value)
{
	t_env	*current;

	current = data->envp_list;
	while(current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}
void print_err_cd(char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, strlen(path));
	write(2, ": ", 2);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, "\n", 1);
}
