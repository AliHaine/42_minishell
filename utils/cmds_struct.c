#include "../minishell.h"

static bool	first_words_node(struct s_cmds *cmds, char *str, int size)
{
	int i;

	i = 0;
	cmds->cmd = malloc(sizeof(char) * size + 1);
	if (!cmds->cmd)
		return (false);
	while (size > 0)
	{
		cmds->cmd[i] = str[i];
		size--;
		i++;
	}
	cmds->cmd[i] = '\0';
	cmds->w = get_origine(str + i);
	return (true);
}

bool	new_words_node(struct s_cmds *cmds, char *str, int size)
{
	int i;
	struct s_cmds *new;

	i = 0;
	if (cmds->cmd != 0)
	{
		new = malloc(sizeof(t_cmds));
		if (!new)
			return (false);
		cmds->next = new;
		new->next = 0;
		new->prev = cmds;
		new->cmd = malloc(sizeof(char) * size + 1);
		if (!new->cmd)
			return (false);
		while (size > 0)
		{
			new->cmd[i] = str[i];
			size--;
			i++;
		}
		new->cmd[i] = '\0';
		new->w = get_origine(str + i);
	}
	else
		return (first_words_node(cmds, str, size));
	return (1);
}

void	free_words_struct(struct s_cmds *cmds)
{
	struct s_cmds	*to_free;

	to_free = cmds;
	while (to_free->prev)
		to_free = to_free->prev;
	cmds = to_free;
	while (to_free->next)
	{
		free(to_free->cmd);
		free(to_free);
		cmds = cmds->next;
		to_free = cmds;
	}
	free(to_free->cmd);
	free(to_free);
}
