#include "../minishell.h"

bool	new_words_node(struct s_cmds *cmds, char *str, int size)
{
	int i;
	struct s_cmds *new;

	i = 0;
	if (cmds->cmd != 0)
	{
		new = malloc(sizeof(t_cmds));
		if (!new)
			return (0);
		cmds->next = new;
		new->next = 0;
		new->prev = cmds;
		new->cmd = malloc(sizeof(char) * size + 1);
		while (size > 0)
		{
			new->cmd[i] = str[i];
			size--;
			i++;
		}
		new->cmd[i] = '\0';
	}
	else
	{
		cmds->cmd = malloc(sizeof(char) * size + 1);
		while (size > 0) {
			cmds->cmd[i] = str[i];
			size--;
			i++;
		}
		cmds->cmd[i] = '\0';
	}
	return (1);
}
