#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	set_signal_prompt(void);
void	set_signal_heredoc(void);
void	set_signal_exec_parent(void);
void	set_signal_exec_child(void);

#endif