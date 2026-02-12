#ifndef TOKENISING_H
# define TOKENISING_H

// The very sole reason of this very header is because I fucking hate norminette and I finalluy understand why people doing minishell creates shit tons of struct liao, anyway fuck norminette.

typedef struct s_tokenising
{
	int singleq;
	int	doubleq;
	int	intoken;
	int	i;
} t_tokenising;

#endif