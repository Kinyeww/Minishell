/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:21:49 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 10:22:17 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void envp_list_clean(t_env **envp_list)
{
	t_env	*temp;

	while (*envp_list != NULL)
	{
		temp = (*envp_list)->next;
		free((*envp_list)->key);
		free((*envp_list)->value);
		free(*envp_list);
		*envp_list = temp;
	}
}