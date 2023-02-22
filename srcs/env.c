#include "../minishell.h"

/* env env env == env \\ env env eng = error */

void print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
}