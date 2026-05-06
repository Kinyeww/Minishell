#define _GNU_SOURCE

#define TOO_MANY_ARG_ERR "minishell : pwd: too many arguments\n"
//pwd should workk if PATH is unset or modified 
int pwd(char **argv, t_data *data)
{
	char *cwd;

	if (argv[1])
		return(write(2, TOO_MANY_ARG_ERR, strlen(TOO_MANY_ARG_ERR)), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
