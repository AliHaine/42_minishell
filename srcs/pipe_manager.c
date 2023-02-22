//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

bool	check_all_pipe(char *cmds)
{
	return (true);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];
	int i;
	int size;
	char *cmd;

	i = 0;
	size = 0;
	while (is_blank(cmds))
		size++;
	cmd = malloc(sizeof(char) * size);
	while ()
	//check if exist

	return (true);
}
