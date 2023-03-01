#include "../minishell.h"

int	check_all_pipe_cmds(char *cmds, struct s_three_int *ti)
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
				if (cmds[ti->a + 1] == '|')
					ti->a++;
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

bool	check_all_quote(char *cmds, struct s_three_int *ti)
{
	int		quote;

	quote = 0;
	while(cmds[ti->a])
	{
		if (cmds[ti->a] == '\'')
		{
			while (cmds[ti->a])
			{
				ti->a++;
			}
		}

		while (cmds[ti->a] && cmds[ti->a] != '\'' || cmds[ti->a] != '"')
		{
			if (cmds[ti->a] == '\'' && quote == 1)

		}
		ti->a++;


	}

	return (true);
}

int check_all(char *cmds, struct s_three_int *ti)
{
	if (check_all_pipe_cmds(cmds, &ti) == 0)
	{
		printf("minishell: command not found\n");
		return (0);

	}
	if ()


	return (1);
}