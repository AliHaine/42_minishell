#include "../minishell.h"

int	ft_execve(char *path, char *const *args, char **env)
{
	if (execve(path, args, env) == -1)
		return (0);
	return (1);
}
