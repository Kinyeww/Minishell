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
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	set_signal_prompt(void)
{
	struct sigaction	sa;

	g_signal = 0;
	sa.sa_handler = handle_sigint_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL); //make sigint do whats specifiec
	signal(SIGQUIT, SIG_IGN); // ignore sigquit?
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

void	set_signal_exec_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); //SIG_IGN (short for "signal ignore") tells the operating system to discard a specific signal instead of taking the default action
}

void	set_signal_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
//SIG_DFL means do the default behaviour 

/*
sq understanding :
- have function sigint_heredoc to print \n

in se_signal_prompt
- clear the 

sa_flag types : 
sigaction : 

bro i gen dk 
*/