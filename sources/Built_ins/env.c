/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:32:23 by syee              #+#    #+#             */
/*   Updated: 2026/05/13 18:21:37 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define TOO_MANY_ARG_ERR "minishell : env: too many arguments\n"

int	env(char **argv, t_data *data)
{
	if (!(*(argv++)))
		return (ft_putstr_fd(TOO_MANY_ARG_ERR, 2), 1);
	print_env_list(data->envp_list);
	return (0);
}
