/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:21:13 by syee              #+#    #+#             */
/*   Updated: 2026/05/14 18:26:25 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void list_add_back(t_env **envp_list, t_env *new)
{
	t_env	*last;

	if (!envp_list || !new)
		return;
	if (*envp_list == NULL)
		*envp_list = new;
	else
	{
		last = list_get_last(*envp_list);
		last->next = new;
	}
	return ;
}
t_env *list_get_last(t_env *envp_list)
{
	if (!envp_list)
    	return NULL;
	while (envp_list->next != NULL)
		envp_list = envp_list->next;
	return (envp_list);
}