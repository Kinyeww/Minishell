/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 22:45:51 by syee              #+#    #+#             */
/*   Updated: 2026/06/08 16:42:58 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define TOO_MANY_ARG_ERR "minishell : pwd: too many arguments\n"

int	pwd(char **argv, t_data *data)
{
	static char	*cwd;

	(void)data;
	if (*(argv + 1))
	{
		write(2, TOO_MANY_ARG_ERR, ft_strlen(TOO_MANY_ARG_ERR));
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
