
/*
removes the entire KEY and acts as if it never existed
even if the vlaue doesnt exist it still returns 0 because the desired outcome which is to make the value not exist is acheived
*/

/*
1. free the KEY and the VALUE & the current itself as its a pointer holding the address to it;
2. attach the next of the previous to the next of the current

*/
void lst_rm(t_env *current, char *argv_key, t_data *data)
{	
	t_env	*temp;

	if (current == data->envp_list)
	{
		if (ft_strcmp(argv_key, current->key) == 0)
		{
			data->envp_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
		}
	}
	else
	{
		if (ft_strcmp(argv_key, current->next->key) == 0)
		{
			temp = current->next;
			free(current->next->key);
			free(current->next->value);
			current->next = current->next->next;
			free(temp);			
		}
	}
}

/*
1. goes thorugh each argument 
2. if it finds the same value inside env then do lst_rm
3. updates to the start of the list and lops to remove the KEY again
things to consider :
- what if its the start
- what if its the end 
*/
int unset(char **argv, t_data *data)
{
	t_env	*current;
	
	argv++;
	while (*argv != NULL)
	{
		current = data->envp_list;
		if (current != NULL && ft_strcmp(*argv, current->key) == 0)
		{
			lst_rm(current, *argv, data);
			current = data->envp_list;
		}
		while (current != NULL && current->next != NULL)
		{
			lst_rm(current, *argv, data);
			current = current->next;
		}
		argv++;
	}
	return (0);
}

/*
conventioally, will free the current and return the next
but still checks via current -> next 
*/