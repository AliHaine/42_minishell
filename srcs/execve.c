#include "../minishell.h"

int	ft_execve(char *const *args, char **env)
{
	char **bash;
	pid_t pid;
	int i;
	int rd;
	
	//pid = fork();
	i = 0;
	rd = -1;
	//if (pid == -1) 
    //    perror("fork failed");
	///else if (pid == 0) 
	{
		bash = ft_split(ft_getenv(env, "PATH"), ':');
		if (!bash)
			return (-1);
		while (rd == -1)
		{
			execve(ft_join(bash[i++], args[0]), args, NULL);
		}
		return (0);
}
