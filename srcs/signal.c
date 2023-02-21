//
// Created by Ali Yagmur on 2/20/23.
//

#include "../minishell.h"

void	ctrl_c()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d()
{
	exit(2);
}
