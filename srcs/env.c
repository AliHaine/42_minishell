#include "../minishell.h"

/* env env env == env \\ env env eng = error */

void print_env(char **env)
{
	int i;

	i = 0;
	env[0] = "Bonsoir";
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
}