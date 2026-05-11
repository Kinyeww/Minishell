/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 06:45:20 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 13:16:32 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

/*
args[0] = export
while (*args)
agrs[1 (onwards)] = 
*/


int export(char **args, t_data *data)
{
    int i;

    i = 1;
    
    if (!args[i])
    {
        print_export_list(data->envp_list);
        return (0);
    }
	// while (args[i])
    // {
    //     if (!is_valid_key(args[i]))
    //     {
    //         write(2, "minishell: export: `", 20);
    //         write(2, args[i], ft_strlen(args[i]));
    //         write(2, "': not a valid identifier\n", 26);
    //         i++;
    //         continue ;
    //     }
    //     add_key_to_list(args[i], data->envp_list);
    //     i++;
    // }
    return (0);
}
//use is alnum
// int is_valid_key(char *args)
// {
//     if (*args == '=' || (*args >= '0' && *args <= '9'))
//         return (0);
//     while (*args != '=')
//     {
//         if ((*args < 'a' && *args > 'z') || (*args < 'A' && *args >'Z'))
//             return (0);
//         args++;
//     }
//     return (1);
// }
// //did the lexer handle the quotes already? 
// void add_key_to_list(char *args, t_env *envp_list)
// {
//     t_env   *new;
//     char    *ptr;
//     int     j;

//     j = 0;
//     new = malloc(sizeof(t_env));
//     ptr = ft_strchr(args, '=');
//     j = ptr - args;
//     new->key = ft_strndup(args, j);
//     new->value = ft_strdup(j + 1);
//     new->next = NULL;
//     envp_list = list_get_last(envp_list);
//     list_add_back(envp_list, new);
// }

void print_export_list (t_env *list)
{
    t_env   *temp_list;
	t_env	*current;
	
	temp_list = NULL;
    envp_list_dup(list, &temp_list);
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

