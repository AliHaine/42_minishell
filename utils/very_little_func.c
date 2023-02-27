#include "../minishell.h"

void	init_three_int(struct s_three_int *ti)
{
	ti->a = 0;
	ti->b = 0;
	ti->c = 0;
}

int	free_str_rzero(char *str)
{
	free(str);
	return (0);
}

void	free_tt(char **str)
{
	int a;

	a = 0;
	while (str[a])
	{
		free(str[a]);
		a++;
	}
	free(str);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (true);
	return (false);
}

bool	is_contain_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

bool is_pipe_or_et(char c)
{
	if (c == '|' || c == '&')
		return (true);
	return (false);
}