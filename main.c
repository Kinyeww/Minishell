#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("av[%d] = %s\n",i ,av[i]);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		printf("envp [%d]:%s\n",i ,envp[i]);
		i++;
	}
	printf("\n---yee shun qi is gay :)---\n");
	return (0);
}