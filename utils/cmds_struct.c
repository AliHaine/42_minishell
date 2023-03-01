#include "../minishell.h"

static bool	first_words_node(struct s_cmds *cmds, char *str, int size)
{
	int i;

	cmds->cmd = malloc(sizeof(char) * size + 1);
	if (!cmds->cmd)
		return (false);
	i = str_copy(cmds->cmd, str, size);
	cmds->w = get_origine(str + i);
	return (true);
}

bool	new_words_node(struct s_cmds *cmds, char *str, int size)
{
	static int a = 0;
	int i;
	struct s_cmds *new;

	printf("here\n");
	if (cmds->cmd || cmds->prev)
	{
		printf("here1\n");
		new = malloc(sizeof(t_cmds));
		if (!new)
			return (false);
		cmds->next = new;
		new->next = 0;
		new->prev = cmds;
		printf("here11\n");
		new->cmd = malloc(sizeof(char) * size + 1);
		if (!new->cmd)
			return (false);
		i = str_copy(new->cmd, str, size);
		new->w = get_origine(str + i);
	}
	else
	{
		printf("here2\n");
		a++;
		return (first_words_node(cmds, str, size));
	}
	printf("end\n");
	return (1);
}

void	free_words_struct(struct s_cmds *cmds)
{
	struct s_cmds	*to_free;

	to_free = cmds;
	while (to_free->prev)
		to_free = to_free->prev;
	while (to_free)
	{
		printf("free\n");
		cmds = to_free->next;
		free(to_free->cmd);
		free(to_free);
		to_free = cmds;
	}
}
