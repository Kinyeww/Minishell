#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

void create_envp_list(t_env **envp_list, char **envp); 
void list_add_back(t_env **envp_list, t_env *new); 
void print_env_list(t_env *list);
t_env *list_get_last(t_env *envp_list);
void envp_list_clean(t_env **envp_list);
void data_clean(t_data *data);

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_data	*data;

	data = malloc (sizeof(t_data));
	*data = (t_data){0};
	create_envp_list(&data->envp_list, envp);
	
	//print_env_list(data->envp_list);
	data_clean(data);

	//loop_main();
	//shell_cleanup();
	//return(); //return the exit code ?

	return (0);
}
//**envp = array of strings 
void create_envp_list(t_env **envp_list, char **envp)
{
	int		i;
	int		j;
	char	*ptr;
	t_env	*new;

	i = 0;
	j = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return;
		ptr = ft_strchr(envp[i], '=');
		j = ptr - envp[i];
		new->key = ft_strndup(envp[i], j);
		new->value = ft_strdup(ptr + 1);
		new->next = NULL;
		list_add_back(envp_list, new);
		i++;
	}
	return ;
}

void list_add_back(t_env **envp_list, t_env *new)
{
	t_env	*last;

	if (!envp_list || !new)
		return;
	if (*envp_list == NULL)
		*envp_list = new;
	else
	{
		last = list_get_last(*envp_list);
		last->next = new;
	}
	return ;
}
t_env *list_get_last(t_env *envp_list)
{
	if (!envp_list)
    	return NULL;
	while (envp_list->next != NULL)
		envp_list = envp_list->next;
	return (envp_list);
}

void envp_list_clean(t_env **envp_list)
{
	t_env	*temp;

	while (*envp_list != NULL)
	{
		temp = (*envp_list)->next;
		free((*envp_list)->key);
		free((*envp_list)->value);
		free(*envp_list);
		*envp_list = temp;
	}
}
void data_clean(t_data *data)
{
	envp_list_clean(&data->envp_list);
	free(data);
}
/*=====testing envp=====*/
void print_env_list(t_env *list)
{
    while (list)
    {
        printf("KEY: %s | VALUE: %s\n", list->key, list->value);
        list = list->next;
    }
}