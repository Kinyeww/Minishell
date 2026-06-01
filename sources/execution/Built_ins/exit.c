/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:42:33 by syee              #+#    #+#             */
/*   Updated: 2026/06/01 20:10:12 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

#define TOO_MANY_ARG_ERR "too many arguments\n"
#define NUMERIC_ARG_ERR ": numeric argument required\n"

void	print_err_exit(char *argv, char *err)
{
	printf ("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(err, 2);
}

int	built_in_exit(char **argv, t_data *data)
{
	int		i;
	long	exit_code;
	
	if (argv[1] != NULL)
	{	
		i = 0;
		while (argv[1][i])
		{
			if (ft_isalpha(argv[1][i]) == 1 || i >= 11)
				return(print_err_exit(argv[1], NUMERIC_ARG_ERR), 2);
			i++;
		}
		exit_code = ft_atol(argv[1]);
		if (exit_code > INT_MAX || exit_code < INT_MIN)
			return(print_err_exit(argv[1], NUMERIC_ARG_ERR), 2);
		else if (argv[2] != NULL) //ok to deref
			return (print_err_exit("", TOO_MANY_ARG_ERR), 2);
		exit_code = ((exit_code % 256) + 256) % 256;
	}
	printf ("exit\n");
	data->exit_flag = true;
	if (argv[1] != NULL)
		return ((int)exit_code);
	return (0);	
}

/*
pipeline :
1. check for numeric & check if it exceeds max_int / min_int via counting len of str
2. check agaisnt INT_MAX  INT_MIN
3. check for amount of arguments
4. if all good , make the exit code using formula
*/

/*
case 1:
exit -9 , output 247 

	what i thought :
	255 + -9 = 246 

	what is happening :
	256 + -9 = 247 (more like (-9 + 256) % 256 = 247)

	256 because 255 is 11111111 in binary, 256 used cus modulo maths..
	formula:
	(-x + 256) % 256
	will not affect the pos cus (10 + 10) % 10 = 0 & 10 % 10 = 0;

case 2:
exit -300 , output 212

	What happening:
	-300 is out of range for 255 therefore will be reduced within the range first
	-300 % 256 = -44
	then it will be converted to positive
	-44 + 256 = 212
	modulo again (this is mostly for positive number)
	212 % 256 = 212

case 3:
exit 4028508425 , output 9

	4028508425 mod 256 = 9
	conclusion : x % 256(last 8 bits) = value 
*/

/*
when exit is called it :
- flags to quit

arguments to handle : 
- if its a valid number
- if its not a valid argument : quit with 0?
 
in main 
- return with data->exit_code

*/