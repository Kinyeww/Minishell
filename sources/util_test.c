//#include "libft_utils.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv)
{
	int i = 0;
	
	pid_t p = fork();
	pid_t k = fork();

	if (p == 0)
	{
		printf ("i am child process, my p is , %d\n", p);	
		printf ("i am child process, my k is , %d\n", k);	
		printf ("process_id = %d child process", getpid());
	}
	else if (k == 0)
	{
		printf ("i am child process, my p is , %d\n", p);	
		printf ("i am child process, my k is , %d\n", k);	
		printf ("process_id = %d child process", getpid());
	}
	else if (p > 0)
	{
		waitpid(p, NULL, 0);
		printf ("i am parent process, my child's process is %d, this is p \n", p);	
		waitpid(k, NULL, 0);
		printf ("i am parent process, my child's process is %d, this is k \n", k);	
		printf ("process_id = %d parent process\n", getpid());
	}
	
}