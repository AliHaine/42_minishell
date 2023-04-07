//
// Created by Ali Yagmur on 4/7/23.
//

#include "../minishell.h"

bool	exec_manager()
{
	t_pipe 		pipes;

	pipes.pid = malloc(sizeof(pid_t) * 2);
	init_three_int(&pipes.ti);
	return (true);
}
