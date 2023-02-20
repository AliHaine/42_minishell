#include "../minishell.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (true);
	return (false);
}
