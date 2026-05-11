/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:57:56 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 12:06:23 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

/*=====testing envp=====*/
void print_env_list(t_env *list)
{
    while (list)
    {
        printf("KEY: %s | VALUE: %s\n", list->key, list->value);
        list = list->next;
    }
}