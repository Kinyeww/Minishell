
#include "../../includes/minishell.h"

/*
args[0] = export
while (*args)
agrs[1 (onwards)] = 
*/
int export(char **args, t_data *data)
{
    int i;

    i = 1;
	while (args[i])
    {
        if (!is_valid_key(args[i]))
        {
            write(2, "minishell: export: `", 20);
            write(2, args[i], ft_strlen(args[i]));
            write(2, "': not a valid identifier\n", 26);
            i++;
            continue ;
        }
        add_key_to_list(args[i], data->envp_list);
        i++;
    }
    return ;
}

int is_valid_key(char *args)
{
    if (*args == '=' || (*args >= '0' && *args <= '9'))
        return (0);
    while (*args != '=')
    {
        if ((*args < 'a' && *args > 'z') || (*args < 'A' && *args >'Z'))
            return (0);
        args++;
    }
    return (1);
}
//did the lexer handle the quotes already? 
void add_key_to_list(char *args, t_env *envp_list)
{
    t_env   *new;
    char    *ptr;
    int     j;

    j = 0;
    new = malloc(sizeof(t_env));
    ptr = ft_strchr(args, '=');
    j = ptr - args;
    new->key = ft_strndup(args, j);
    new->value = ft_strdup(j + 1);
    new->next = NULL;
    envp_list = list_get_last(envp_list);
    list_add_back(envp_list, new);
}
void print_export_list (t_data *list)
{

}

/*
1. check with mel's minishell
    - how to print export
    - how to handle quotations
2. */