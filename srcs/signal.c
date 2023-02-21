//
// Created by Ali Yagmur on 2/20/23.
//

#include "../minishell.h"

void	ctrl_c()
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//rl_on_new_line();
}

void	ctrl_d()
{
	exit(2);
}
