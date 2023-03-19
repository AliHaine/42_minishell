#include "../minishell.h"

static bool	second_word(char *cmds, char **cmd_arg, int size)
{
	int	i;
	int	save;

	i = 0;
	save = size;
	while (cmds[size + i] && (is_redir_char(cmds[size + i])
		|| cmds[size + i] == ' '))
		i++;
	while(cmds[size + i])
		size++;
	cmd_arg[1] = malloc(sizeof(char) * size + 1);
	if (!cmd_arg[1])
		return (0);
	size = 0;
	while(cmds[save + i])
	{
		cmd_arg[1][size] = cmds[save + i];
		save++;
		size++;
	}
	cmd_arg[1][size] = '\0';
	return (true);
}

static int	first_word(char *cmds, char **cmd_arg)
{
	int	i;

	i = 0;
	while(cmds[i] && !is_redir_char(cmds[i])
		&& cmds[i] != ' ')
		i++;
	cmd_arg[0] = malloc(sizeof(char) * i + 1);
	if(!cmd_arg[0])
		return (0);
	i = 0;
	while(cmds[i] && !is_redir_char(cmds[i])
		&& cmds[i] != ' ')
	{
		cmd_arg[0][i] = cmds[i];
		i++;
	}
	cmd_arg[0][i] = '\0';
	return (i);
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
