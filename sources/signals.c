#define _POSIX_C_SOURCE 200809L
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal = 0;

static void	handle_sigint_prompt(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_heredoc(int signum)
{
	g_signal = signum;
	close(STDIN_FILENO);
}

void	set_signal_prompt(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = handle_sigint_prompt;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
//depends on who is waiting 
//
void	set_signal_exec_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
//need create a funciton when if child, and theres sigint, or sig


//SIG_DFL means do the default behaviour 
//CTRL-D sends EOF to readline to indicate end

/*
if (cmd->next) //if there is pipe
{
	fork()
	if (child)
	{
		set_signal_exec_child();
		if (built_in)
			run built_in;
		if (binary)
		{
			fork();
			if (child)
				set_signal_exec_child();
			if (parent)
				set_signal_exec_parent();
		}				
	}
	if (parent)
		set_signal_exec_parent();
}
*/

