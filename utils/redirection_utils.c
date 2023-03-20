#include "../minishell.h"

void	write_to_file(int fd, char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}