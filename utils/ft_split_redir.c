#include "../minishell.h"

static bool	second_word(char *cmds, char **cmd_arg, int size)
{
	int	i;
	int	save;
	int a;

	i = 0;
	save = 0;
	a = size;
	while (cmds[size + i] && (is_redir_char(cmds[size + i])
		|| cmds[size + i] == ' '))
		i++;
	while(cmds[size + i])
	{
		size++;
		save++;
	}
	cmd_arg[1] = malloc(sizeof(char) * save + 1);
	if (!cmd_arg[1])
		return (0);
	save = 0;
	while(cmds[a + i])
	{
		cmd_arg[1][save] = cmds[a + i];
		save++;
		a++;
	}
	cmd_arg[1][save] = '\0';
	return (true);
}

static int	first_word(char *cmds, char **cmd_arg)
{
	int	i;
	int a;

	i = 0;
	a = 0;
	while(cmds[a] && cmds[a] != ' ')
		a++;
	if (cmds[a] == ' ')
		a++;
	if (!cmds[a])
		return (0);
	while(cmds[i + a] && !is_redir_char(cmds[i + a])
		&& cmds[i + a] != ' ')
		i++;
	cmd_arg[0] = malloc(sizeof(char) * i + 1);
	if(!cmd_arg[0])
		return (0);
	i = 0;
	while(cmds[i + a] && !is_redir_char(cmds[i + a])
		&& cmds[i + a] != ' ')
	{
		cmd_arg[0][i] = cmds[i + a];
		i++;
	}
	cmd_arg[0][i++] = '\0';
	return (i + a);
}

char	**ft_split_redir(char *cmds, int w)
{
	int size;
	char **cmd_arg;

	cmd_arg = malloc(sizeof(char *) * 3);
	if (!cmd_arg)
		return (0);
	size = first_word(cmds, cmd_arg);
	second_word(cmds, cmd_arg, size);
	cmd_arg[2] = 0;
	return(cmd_arg);
}
