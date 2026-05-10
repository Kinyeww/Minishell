#include "../includes/parsing.h"
#include <stdlib.h>
#include <stdio.h>




int	add_redir(t_cmd	*cmd_list, t_token_type r_type, char *file_name)
{
	t_redir	*new;
	t_redir	*tmp;

	new = new_redir(r_type, file_name);
	if (!new)
		return (0);
	if (!cmd_list->redir)
	{
		cmd_list->redir = new;
		return (1);
	}
	tmp = cmd_list->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	add_arg(t_cmd *cmd_list, char *content)
{

}

static t_redir	*new_redir()