#include "../minishell.h"

// ls //

void ls(char **cmd)
{
	struct dirent *ent;
	DIR *dir;

	if (cmd[0] && cmd[1])
	{
		printf("ls: %s: No such file or directory\n", cmd[1]);
		return ;
	}
	if ((dir = opendir(".")) != NULL) 
	{

        	while ((ent = readdir(dir)) != NULL) 
			{
				if (ent->d_name[0] != '.')
				{
            		printf("%s       ", ent->d_name);
				}
			}
			printf("\n");
        	closedir(dir);
    } 
	else 
        perror("");
}