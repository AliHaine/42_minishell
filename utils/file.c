#include "../minishell.h"

void	go_to_end_of_file(int fd)
{
	char *str;

	str = get_next_line(fd);
	while (str)
	{
		add_history(str);
		str = get_next_line(fd);
	}
}


bool	write_to_histo(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	return (true);
}