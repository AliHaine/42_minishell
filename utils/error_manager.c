#include "../minishell.h"

int	check_all_pipe_cmds(char *cmds, struct s_three_int ti)
{
	char *str;

	while (cmds[ti.a])
	{
		while (cmds[ti.a + ti.b] && !is_space(cmds[ti.a + ti.b]))
			ti.b++;
		str = ft_substr(cmds, ti.a, ti.b);
		if (get_cmd(str) == 0)
			return (free_str_rzero(str));
		free(str);
		while (cmds[ti.a])
		{
			if (cmds[ti.a] == '|')
			{
				if (cmds[ti.a + 1] == '|')
					ti.a++;
				ti.a += 2;
				ti.c++;
				break;
			}
			ti.a++;
		}
		ti.b = 0;
	}
	return (ti.c += 1);
}

bool	check_all_quote(struct s_cmds *cmds)
{
	int		i;
	int 	size;

	i = 0;
	size = 0;
	while (cmds)
	{
		while (cmds->line[size])
			size++;
		while (cmds->line[i] && cmds->line[i] != ' ')
			i++;
		i++;
		if (cmds->line[i] == '\'' || cmds->line[i] == '"')
		{
			if (cmds->line[i] == '\'')
			{
				if (cmds->line[size - 1] != '\'')
					return (false);
			}
			else
				if (cmds->line[size - 1] != '"')
					return (false);
		}
		i = 0;
		size = 0;
		cmds = cmds->next;
	}
	return (true);
}

void	file_error()
{

}