#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

typedef struct s_heredoc
{
	int		fd;
	int		stat;
	char	*line;
}	t_heredoc;

#endif