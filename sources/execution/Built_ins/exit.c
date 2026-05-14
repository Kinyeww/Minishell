/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:42:33 by syee              #+#    #+#             */
/*   Updated: 2026/05/14 21:07:20 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
when exit is called it :
- flags to quit

arguments to handle : 
- if its a valid number
- if its not a valid argument : quit with 0?
 
in main 
- return with data->exit_code

*/

int	built_in_exit(char **argv, t_data *data)
{
	int	i;

	/*
	- if the argv[1] isnt NULL, argv[2] might be NULL
		, therefore it's alright to dereference it
	*/
	if (argv[1] != NULL)
	{
		int	error_code;
		
		//if (ft_isalpha(argv[1]) == 1 || over_MAX_MIN(argv[1]) == 0)
		if (ft_isalpha(argv[1]) == 1 )
		{
			printf ("exit\n");
			ft_putstr_fd("minishell: exit:", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			data->exit_code = true;	
			return (1);
		}
		else if (argv[2] != NULL)
		{
			printf ("exit\n");
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			error_code = ft_atoi(argv[1]);
			error_code = ((error_code % 256) + 256) % 256;
			data->exit_code = true;
			return (error_code);
		}
	}
	printf ("exit\n");
	data->exit_code = true;
	return (0);
}

/*
if it exceeds maxint it says numeric argument reqiured
if its a negative value then it will wrap 
*/

/*
types of operators:
- ternary
- binary : & , << , 
- unary = ! - 
- bitwise ; 
*/