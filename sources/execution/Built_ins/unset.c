/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:35:19 by syee              #+#    #+#             */
/*   Updated: 2026/05/13 18:26:29 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- removes the entire KEY and acts as if it never existed
- even if the value doesnt exist it still returns 0 because the desired outcome
	which is to make the value not exist is acheived
code :
1. free the KEY and the VALUE & the curr itself as its a pointer holding 
	the address to it
2. attach the next of the previous to the next of the curr
*/
int	unset(char **argv, t_data *data)
{
	argv++;
	while (*argv != NULL)
	{
		envp_list_remove(&data->envp_list, *argv);
		argv++;
	}
	return (0);
}

void	envp_list_remove(t_env **envp_list, char *argv_key)
{
	t_env	*curr;
	t_env	*temp;

	curr = *envp_list;
	while (curr)
	{
		if (curr == *envp_list && ft_strcmp(argv_key, curr->key) == 0)
		{
			*envp_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			curr = *envp_list;
			continue ;
		}
		if ((curr->next != NULL) && ft_strcmp(argv_key, curr->next->key) == 0)
		{
			temp = curr->next;
			free(curr->next->key);
			free(curr->next->value);
			curr->next = curr->next->next;
			free (temp);
		}
		curr = curr->next;
	}
}
