/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:44:11 by syee              #+#    #+#             */
/*   Updated: 2026/05/13 18:08:59 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "minishell.h"

#define TOO_MANY_ARG_ERR "minishell :cd: too many arguments\n"
#define HOME_NOT_SET "minishell :cd: HOME not set\n"
#define OLDPWD_NOT_SET "minishell :cd: OLDPWD not set\n"
#define GETCWD_FAIL "minishell :cd: getcwd failed\n"

/*
getcwd (str, str size);
strerror (errno);
chdir (path); <- change path

expected behaviours:
0 if success
1 if fail

in order of checking :
1. too many arguments
2. fail to get current working directory 
3. if only cd , when HOME not set , if set path = home
4. if - (go to prev directory) , when OLDPWD is unset 
5. if got 1 arg (working)
	5a. if not a dir / dir does not exist / 

Should work cases :
../
-
/

should not work :
~

edge cases if youre insane :

*/

int	cd(char **argv, t_data *data)
{
	char	*path;
	char	*home;
	char	old_dir[1024];

	if (argv[1] && argv[2])
		return (ft_putstr_fd(TOO_MANY_ARG_ERR, 2), 1);
	if (!getcwd(old_dir, sizeof(old_dir)))
		return (ft_putstr_fd(GETCWD_FAIL, 2), 1);
	if (!argv[1])
	{
		home = get_env_value(data, "HOME");
		if (!home)
			return (ft_putstr_fd(HOME_NOT_SET, 2), 1);
		path = home;
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = get_env_value(data, "OLDPWD");
		if (!path)
			return (ft_putstr_fd(OLDPWD_NOT_SET, 2), 1);
		printf("%s\n", path);
	}
	else
		path = ft_strdup(argv[1]);
	return (change_dir(path, old_dir, data));
}

char	*get_env_value(t_data *data, char *key)
{
	t_env	*current;
	char	*return_str;

	current = data->envp_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return_str = ft_strdup(current->value);
			return (return_str);
		}
		current = current->next;
	}
	return (NULL);
}

/*
will likely break if open another terminal and delete cwd
*/
int	change_dir(char *path, char *old_path, t_data *data)
{
	char	current_path[1024];

	if (chdir(path) != 0)
	{
		print_err_cd(path);
		free(path);
		return (1);
	}
	update_env(data, "OLDPWD", old_path);
	getcwd(current_path, sizeof(current_path));
	update_env(data, "PWD", current_path);
	free(path);
	return (0);
}

void	update_env(t_data *data, char *key, char *value)
{
	t_env	*current;

	current = data->envp_list;
	while (current != NULL)
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

void	print_err_cd(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}
