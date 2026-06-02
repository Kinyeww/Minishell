/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 06:45:20 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 14:44:36 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>


void	print_err_export(char *key)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	write(2, "\n", 1);
}
int export(char **argv, t_data *data)
{
	int return_code;
	int	i;

	i = 1;
	return_code = 0;
	if (!argv[i])
	{
		print_export_list(data->envp_list);
		return (return_code);
	}
	while (argv[i])
	{
		if (!is_valid_key(argv[i]))
		{
			print_err_export(argv[i]);
			i++;
			return_code = 1;
			continue ;
		}
		add_key_to_list(argv[i], data->envp_list);
		return_code = 0;
		i++;
	}
	return (return_code);
}

/*
false cases to consider :
42USER      # starts with number
MY-VAR      # '-' invalid
MY VAR      # spaces invalid
VAR!        # '!' invalid
=HELLO      # cannot start with '='
*/
bool is_valid_key(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[i]) && argv[i] != '_')
		return (false);
	i++;
	while (argv[i] && ft_isalnum(argv[i]))
		i++;
	//cannot be based on if there is = or not
	return (argv[i] == '=' || argv[i] == '\0');
}

void add_key_to_list(char *argv, t_env *envp_list)
{
	t_env	*new;
	char	*ptr;
	int		j;

	j = 0;
	new = malloc(sizeof(t_env));
	ptr = ft_strchr(argv, '=');
	if (!ptr)
	{
		new->key = ft_strndup(argv, j);
		new->value = ft_strdup("");
	}
	else
	{
		j = ptr - argv;
		new->key = ft_strndup(argv, j);
		new->value = ft_strdup(ptr + 1);
	}
	new->next = NULL;
	list_add_back(&envp_list, new);
}

void print_export_list (t_env *envp_list)
{
	t_env	*temp_list;
	t_env	*current;
	
	temp_list = NULL;
	envp_list_dup(envp_list, &temp_list);
	envp_bubble_sort_list(&temp_list);
	current = temp_list;
	while (current != NULL)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
	envp_list_clean(&temp_list);
}

void envp_list_dup(t_env *original_list, t_env **temp_list)
{
	t_env   *current;
	
	while (original_list)
	{
		current = malloc(sizeof(t_env));
		current->key = ft_strdup(original_list->key);
		current->value = ft_strdup(original_list->value);
		current->next = NULL;
		list_add_back(temp_list, current);
		original_list = original_list->next;
	}
}

