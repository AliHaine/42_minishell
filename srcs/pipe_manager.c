//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

static bool	check_all_pipe(char *cmds, int i, int o)
{
	char *str;

	while (cmds[o])
	{
		while (cmds[o + i] && !is_space(cmds[o + i]))
			i++;
		str = ft_substr(cmds, o, i);
		if (get_cmd(str) == 0)
		{
			free(str);
			return (false);
		}
		free(str);
		while (cmds[o])
		{
			if (cmds[o] == '|')
			{
				o += 2;
				break;
			}
			o++;
		}
		i = 0;
	}
	return (true);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];

	if (check_all_pipe(cmds, 0, 0) == true)
		return (true);
	else
		printf("minishell: command not found\n");
	return (false);
}