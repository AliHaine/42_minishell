//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

bool	check_all_pipe(char *cmds)
{
	int	i;
	int o;
	char *str;

	i = 0;
	o = 0;
	while (cmds[o])
	{
		while (cmds[o + i] && !is_space(cmds[o + i]))
			i++;
		str = malloc(sizeof(char) * (i + 1));
		str[i] = '\0';
		i--;
		while (i > -1)
		{
			printf("%d\n", i);
			str[i] = cmds[o];
			o++;
			i--;
		}
		printf("ss %s\n", str);
		if (get_cmd(str) == 0)
			return (false) ;
	}
	return (true);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];

	if (check_all_pipe(cmds) == true)
		return (true);
	return (false);
}
