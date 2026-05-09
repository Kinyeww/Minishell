#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	t_data	*data;

	data = malloc (sizeof(t_data));
	*data = (t_data){0};
	create_envp_list(&data->envp_list, envp); //if envp list fails?
	//loop_main();
	//shell_cleanup();
	//return(); //return the exit code ?

	return (0);
}
//**envp = array of strings 
void create_envp_list(t_env **envp_list, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return;
		new->key = get_key(envp[i]); //ft_strndup(envp[]);
		new->value = get_value(envp[i]);
		new->next = NULL;
		add_back(envp_list, new);
		i++;
	}
	return;
}

void copy_envp(t_data *data, char **envp)
{
	
	char	*ptr;
	int		i;
	int		j;

	
	
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
//delet envp
//replace envp
//

void list_add_back(t_env **envp_list, t_data **data)
{
	//if first
	//if last
	//if in between
}

void list