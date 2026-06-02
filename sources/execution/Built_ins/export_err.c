/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:51:53 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 18:52:16 by syee             ###   ########.fr       */
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
