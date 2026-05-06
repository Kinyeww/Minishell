#include <stdlib.h>
//env with no options or arguments, so only printing all there is inside env?
#define TOO_MANY_ARG_ERR "minishell : env: too many arguments\n" //might be an error later 

int env(char **argv, t_data *data)
{
	int		argc;
	t_env	*current;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc > 1)
		return (write(2, TOO_MANY_ARG_ERR, ft_strlen(TOO_MANY_ARG_ERR)), 1);
	
	current = data->envp_list;
	while (current != NULL)
	{
		printf("%s",current->key);
		printf("=%s\n",current->value);
		current = current->next;
	}
	return (0);
}