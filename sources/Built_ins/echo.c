#include "ast.h"
#include <stdlib.h>

//check for -n 
//check for the words to print 
//print out using write  

#define NO_NEWLINE 0
#define YES_NEWLINE 1
/*
-assuming the values are passed into as argv = "echo", "-n", "tetx"
*/
int check_n(char **cmd) //true returns 1
{
	if (ft_strcmp(cmd[1], "-n"))
		return (YES_NEWLINE);
	else 
		return(NO_NEWLINE);
}

/*
check for -n 
if there is newline flag then start printing at cmd[2] (after the -n)
after every cmd[i], need space 
if there is a newline then end with \n
prints to stdout ??
*/
int echo (char **argv) // i have to know what fd t is 
{
	int newline_flag;
	int i;
	i = 0;

	newline_flag = check_n(argv);
	if (newline_flag == YES_NEWLINE)
		i = 2;
	while (argv[i] != NULL)
	{
		write (1, argv[i], ft_strlen(argv[i]));
		write (1, " ", 1);
	}
	if (newline_flag == YES_NEWLINE)
		write(1, "/n", 1);

	return (0); //exit 0 on success 
}

