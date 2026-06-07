/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:51:53 by syee              #+#    #+#             */
/*   Updated: 2026/06/07 16:05:05 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_export(char *key)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	write(2, "\n", 1);
}

void	envp_list_dup(t_env *original_list, t_env **temp_list)
{
	t_env	*current;

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
