#include "../minishell.h"

/* pwd */

void pwd(void)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	printf("%s\n", path);
}

