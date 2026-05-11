/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:35:19 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 21:04:00 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- removes the entire KEY and acts as if it never existed
- even if the value doesnt exist it still returns 0 because the desired outcome
	which is to make the value not exist is acheived
code :
1. free the KEY and the VALUE & the current itself as its a pointer holding 
	the address to it
2. attach the next of the previous to the next of the current
*/
int unset(char **argv, t_data *data)
{	
	argv++;
	while (*argv != NULL)
	{
		envp_list_remove(&data->envp_list, *argv);
		argv++;
	}
	return (0);
}

void envp_list_remove(t_env **envp_list, char *argv_key)
{
	t_env	*current;
	t_env	*temp;

	current = *envp_list;
	while (current)
	{
		if (current == *envp_list && ft_strcmp(argv_key, current->key) == 0)
		{
			*envp_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = *envp_list;
			continue ;
		}
		if ((current->next != NULL) && ft_strcmp(argv_key, current->next->key) == 0)
		{
			temp = current->next;
			free(current->next->key);
			free(current->next->value);
			current->next = current->next->next;
			free (temp);
		}
		current = current->next;
	}
}
