/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:01:32 by syee              #+#    #+#             */
/*   Updated: 2026/05/29 15:02:02 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_envp_list(t_env **envp_list, char **envp)
{
	int		i;
	int		j;
	char	*ptr;
	t_env	*new;

	i = 0;
	j = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		ptr = ft_strchr(envp[i], '=');
		j = ptr - envp[i];
		new->key = ft_strndup(envp[i], j);
		new->value = ft_strdup(ptr + 1);
		new->next = NULL;
		list_add_back(envp_list, new);
		i++;
	}
	return ;
}