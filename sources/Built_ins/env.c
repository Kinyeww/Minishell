/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:32:23 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 21:16:39 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define TOO_MANY_ARG_ERR "minishell : env: too many arguments\n" //might be an error later 

int env(char **argv, t_data *data)
{
	if (!(*(argv++)))
	{
		write(2, TOO_MANY_ARG_ERR, ft_strlen(TOO_MANY_ARG_ERR));
		return(1);
	}
	print_env_list(data->envp_list);
	return (0);
}
