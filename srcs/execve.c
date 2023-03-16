 #include "../minishell.h"

int	ft_execve(char *const *args, char **env)
{
	char **bash;
	int i;
	int rd;

	i = 0;
	rd = -1;
	bash = ft_split(ft_getenv(env, "PATH"), ':');
	if (!bash)
		return (-1);
	while (rd == -1)
	{
		rd = execve(ft_join(bash[i++], args[0]), args, NULL);
	}
	return (0);
}
