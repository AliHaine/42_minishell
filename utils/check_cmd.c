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

int get_cmd(char *cmd)
{
	if (ft_strcmp("echo", cmd))
		return (1);
	else if (ft_strcmp("pwd", cmd))
		return (2);
	else if (ft_strcmp("exit", cmd))
		return (3);
	else if (ft_strcmp("env", cmd))
		return (4);
	else if (ft_strcmp("unset", cmd))
		return (5);
	else if (ft_strcmp("export", cmd))
		return (6);
	else if (ft_strcmp("cd", cmd))
		return (7);
	return (0);
}

static void check_bulltin(char **cmd, char **env, struct s_minishell *ms)
{
	if (!cmd[0])
		return ;
	else if (get_cmd(cmd[0]) == 1)
		echo(cmd);
	else if (get_cmd(cmd[0]) == 2)
		pwd();
	else if (get_cmd(cmd[0]) == 3)
		ms->exit = 0;
	else if (get_cmd(cmd[0]) == 4)
		print_env(env);
	else if (get_cmd(cmd[0]) == 5)
	{
		if (cmd[1] && env[0])
			unset(cmd[1] ,env, 0);
		else
			printf("\n");
	}
	else if (get_cmd(cmd[0]) == 6)
		export(cmd, env);//
	else if (get_cmd(cmd[0]) == 7)
		cd(cmd, env);
	else
		printf("minishell: %s: command not found\n", cmd[0]);
	return ;
}

// check_all_cmd //

void check_all_cmd(char *line, char **env, struct s_minishell *ms)
{
	char **args;

	args = ft_split(line, ' ');
	if (!args)
		return ;
	check_bulltin(args, env, ms);
	free_tt(args);
}