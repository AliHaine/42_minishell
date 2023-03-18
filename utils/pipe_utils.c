#include "../minishell.h"

static int	ft_strcmp_to_space(char *a, char *b)
{
    int	i;

    i = 0;
    while (a[i] && a[i] != ' ')
    {
        if (a[i] != b[i])
            return (0);
        i++;
    }
    return (1);
}

bool	pipe_init(int pipes[][2], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pipe(pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

void	close_all_pipes(int pipes[][2], int size)
{
	while (size > 0)
	{
		close(pipes[size - 1][0]);
		close(pipes[size - 1][1]);
		size--;
	}
}
