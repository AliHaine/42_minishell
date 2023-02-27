//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

static bool	set_cmds_to_tab(char **tab, char *cmds, int size)
{
	
	return (true);
}

static int	check_all_pipe(char *cmds, struct s_three_int *ti)
{
	char *str;

	while (cmds[ti->a])
	{
		while (cmds[ti->a + ti->b] && !is_space(cmds[ti->a + ti->b]))
			ti->b++;
		str = ft_substr(cmds, ti->a, ti->b);
		if (get_cmd(str) == 0)
			return (free_str_rzero(str));
		free(str);
		while (cmds[ti->a])
		{
			if (cmds[ti->a] == '|')
			{
				ti->a += 2;
				ti->c++;
				break;
			}
			ti->a++;
		}
		ti->b = 0;
	}
	return (ti->c += 1);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];
	char **tab;
	struct s_three_int ti;

	init_three_int(&ti);
	if (check_all_pipe(cmds, &ti) > 0)
	{
		printf("ss //%d\n", ti.c);
		return (true);
	}
	else
		printf("minishell: command not found\n");
	return (false);
}
