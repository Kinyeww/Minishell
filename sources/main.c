#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	check_first(char *line);

/*
count the amount of envp 
malloc 
*/

char *ft_strdup(char *string)
{
	int i; 
	char *str;

	if (!string)
        return (NULL);
	i = 0;
	while (string[i])
		i++;
	str = malloc(i + 1);
	i = 0;
	while (string[i])
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strchr(char *string, char c)
{
	int i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (string + i);
	}
	return (NULL);
}


char *ft_strndup(char *string , int size)
{
	int		i;
	char	*return_str;

	i = 0;
	if (!string)
		return (NULL);
	return_str = malloc(size + 1);
	while (string[i] != '\0')
	{
		return_str[i] = string[i];
		i++;
	}
	return (return_str);
}
/*
1. create an array of envp struct, on when more values need to be added then malloc
2. 
*/
void copy_envp(t_data *data, char **envp)
{
	int		envp_count;
	char	*ptr;
	int		i;
	int		j;

	envp_count = 0;
	while (envp[envp_count] != NULL)
		envp_count++;
	data->envp_list = malloc(sizeof(t_env) * (envp_count + 1));
	j = 0;
	while (j < envp_count)
	{
		ptr = ft_strchr(envp[j], '=');
		i = ptr - envp[j];
		data->envp_list[j].key = ft_strndup(envp[j], i);
		data->envp_list[j].value = ft_strndup(envp[j] + i + 1, ft_strlen(envp[j] + i + 1));
		if (j == envp_count)
			data->envp_list[j].next = NULL;
		else
			data->envp_list[j].next = &data->envp_list[j + 1];
		j++;
	}
}
//need to make a copy of the envp to manipulate , whenever print export it manipulates the oopy of envp instead
int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_token	*tokens;

	(void) ac;
	(void) av;
	copy_envp(&data, envp);
	while (1)
	{
		line = readline("Minishell$ ");
		if (check_first(line) == 0)
			continue ;
		tokens = tokenising(line);
		if (tokens == NULL)
			return (1);
		tokens = parsing(tokens);
		//sq execution command here ?
		free(line);
	}
	return (0);
}
//fake ast to test
int main(int ac, char **av, char **envp) //tehcnically i do not need to use anything from the parsing for now 
{
	(void)ac;
	(void)av;
	t_ast ast1;
	t_ast ast2;

	char *ast_arr[4];
	ast1.token_type = COMMAND;
	ast1.left = NULL; //should i have a funciton to set it as null in the first place : yes
	ast1.right = NULL;
	ast1.argv = ast_arr;
	ast1.argv[0] = "ehco";
	ast1.argv[1] = "-n";
	ast1.argv[2] = "hello";
	ast1.argv[3] = NULL;


	execute_ast();
	
}

static int	check_first(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		free (line);
		return (0);
	}
	return (1);
}