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

static void check_bulltin(char **cmd, char **env, struct s_minishell *ms)
{
	if (!cmd[0])
		return ;
	else if (ft_strcmp("echo", cmd[0]) == 1)
		echo(cmd);
	else if (ft_strcmp("pwd", cmd[0]) == 1)
		pwd();
	else if (ft_strcmp("exit", cmd[0]) == 1)
		ms->exit = 0;
	else if (ft_strcmp("env", cmd[0]) == 1)
		print_env(env);
	else if (ft_strcmp("unset", cmd[0]) == 1)
	{
		if (cmd[1] && env[0])
			unset(cmd[1] ,env, 0);
		else
			printf("\n");
	}
	else if (ft_strcmp("export", cmd[0]) == 1)
		export(cmd, env);//
	else if (ft_strcmp("cd", cmd[0]) == 1)
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