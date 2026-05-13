#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>



/*
to-do
1. parse tokens to t_redir
2. expand env like $HOME = /home/king
3. make execution without pipe works, then with redir, then with pipes

echo hi > out      // REDIR_OUT: create/truncate file, stdout goes there
echo hi >> out     // APPEND: create/append file, stdout goes there
cat < in           // REDIR_IN: stdin comes from file
cat << EOF         // HEREDOC: stdin comes from temporary heredoc input
*/

t_token	*expand(t_token *tokens, char **envp)
{
	(void)envp;
	printf("--- expanding ---\n");
	printf("no error found\n");
	return (tokens);
}

