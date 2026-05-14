#include "libft_utils.h"
#include <stdio.h>

int main (int argc, char **argv)
{
	int i = 0;
	while (argv[1][i])
	{
		printf("%d\n",ft_isalpha(argv[1][i]));
		i++;
	}
	//printf("%d\n",ft_atoi(argv[1]));
}