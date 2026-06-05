#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void	run_shell(t_data *data);

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		exit_code;

	(void) ac;
	(void) av;
	init_data(&data, envp);
	rl_catch_signals = 0;
	run_shell(&data);
	exit_code = data.exit_code;
	data_clean(&data);
	return (exit_code);
}

static void	run_shell(t_data *data)
{
	char	*line;

	while (1)
	{
		set_signal_prompt();
		line = readline("Minishell$: ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!execute_line(line, data))
			break ;
	}
}
