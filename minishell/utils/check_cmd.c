#include "../minishell.h"

// ft_strcmp //

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	while (a[i])
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

void check_bulltin(char **cmd)
{
	if (ft_strcmp("echo", cmd[0]) == 1)
		echo(cmd);
	else if (ft_strcmp("pwd", cmd[0]) == 1)
		pwd();
	else if (ft_strcmp("exit", cmd[0]) == 1)
		exit_shell();
	else
		printf("minishell: %s: command not found\n", cmd[0]);
}

// check_all_cmd //

void check_all_cmd(char *line)
{
	char **args;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	check_bulltin(args);
	free(args);
}