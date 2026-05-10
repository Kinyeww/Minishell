#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	check_first(char *line);

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void) ac;
	(void) av;
	(void) envp;
	while (1)
	{
		line = readline("Minishell$ ");
		if (check_first(line) == 0)
			continue ;
		tokens = tokenising(line);
		if (tokens == NULL)
			return (1);
		cmds = parsing(tokens);
		// tokens = expand(cmds, envp);
		free(line);
	}
	return (0);
}

static int	check_first(char *line) //empty line check
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