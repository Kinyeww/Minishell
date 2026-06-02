/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bubble_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:39:39 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 20:39:19 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

/*
unlike array swap, it does it numbe of times of the list size
no shrinking or stopping at swapped portion 
swapping the strings within rather than the entire node due to convineince
should probably practice how to swap nodes but idea is to create /
a func to swap then move node foward
*/

void	envp_bubble_sort_list(t_env **temp_list)
{
	t_env	*i;
	t_env	*j;
	char	*tmp_key;
	char	*tmp_value;

	i = *temp_list;
	while (i)
	{
		j = *temp_list;
		while (j && j->next)
		{
			if (ft_strcmp(j->key, j->next->key) > 0)
			{
				tmp_key = j->key;
				tmp_value = j->value;
				j->key = j->next->key;
				j->value = j->next->value;
				j->next->key = tmp_key;
				j->next->value = tmp_value;
			}
			j = j->next;
		}
		i = i->next;
	}
}
