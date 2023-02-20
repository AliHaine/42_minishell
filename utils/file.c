#include "../minishell.h"

bool	write_to_histo(char *str, int fd)
{
	int i;

	i = 0;
	str = get_next_line(fd);
	while(str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (true);
}
