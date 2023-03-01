#include "../minishell.h"

bool	is_blank(char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			size++;
		i++;
	}
	if (size == 0)
		return (true);
	return (false);
}

int get_origine(char *cmds)
{
	int i;

	i = 0;
	while (is_space(cmds[i]))
		i++;
	while (cmds[i])
	{
		if (cmds[i] == '|' && cmds[i + 1] == '|')
			return (1);
		else if (cmds[i] == '|')
			return (2);
		else if (cmds[i] == '&' && cmds[i + 1] == '&')
			return (3);
		else
			return (0);
	}
	return (0);
}

int get_allstr_word_size(char *str)
{
	int size;
	int mode;

	size = 0;
	mode = 0;
	while (str[size])
	{
		if (str[size] == '|' || str[size] == '&' && mode == 0)
		{
			/*if (str[size + 1] && str[size + 1] == '|' || str[size + 1] == '&')
				size++;*/
			break ;
		}
		if (str[size] == '"' || str[size] == '\'' && mode == 0)
		{
			if (mode == 0)
				mode = 1;
			else
				break ;
		}
		size++;
	}
	if (!str[size])
		return (size);
	return (size - 1);
}
