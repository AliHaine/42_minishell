#include "../minishell.h"

static char	*get_current_word(char *s, int *a)
{
	int	i;
	char *new;

	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a]))
	{
		i++;
		*a = *a + 1;
	}
	new = malloc(sizeof(char) * i + 1);
	*a = *a - i;
	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a]))
	{
		new[i++] = s[*a];
		*a = *a + 1;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split_redir(t_cmds *cmds, int w)
{
	int size;
	int	i;

	size = 0;
	i = 0;
	cmds->cmd = get_current_word(cmds->line, &i);
	while (cmds->line[i] && cmds->line[i] == ' ')
		i++;
	cmds->args = malloc(sizeof(char *) * 10);
	while (cmds->line[i])
	{
		cmds->args[size] = get_current_word(cmds->line, &i);
		size++;
		while (cmds->line[i] && cmds->line[i] == ' ')
			i++;
	}
	cmds->args[size] = NULL;
	size = 0;
	printf("cmd = %s---------------\n", cmds->cmd);
	while (cmds->args[size])
	{
		printf("res = %s\n", cmds->args[size]);
		size++;
	}
	return(0);
}