#include "../minishell.h"

bool	pipe_init(int pipes[][2])
{
	int	i;

	i = 0;
	while (i < 19)
	{
		if (pipe(pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

void	close_all_pipes(int pipes[][2])
{
	int i;

	i = 0;

	while (i < 19)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
