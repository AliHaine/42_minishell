#include "../minishell.h"


int	ft_execve(char *const *args, char **env)
{
	char **bash;
	pid_t pid;
	int i;
	int test;
	
	pid = fork();
	i = 0;
	test = -1;
	if (pid == 0) 
	{
		bash = ft_split(ft_getenv(env, "PATH"), ':');
		if (!bash)
			return (-1);
		while (test < 0)
		{
			test = execve(ft_join(bash[i++], args[0]), args, NULL);
		}
	}
	else
		waitpid(pid, &test, 0);
	return (0);
}
