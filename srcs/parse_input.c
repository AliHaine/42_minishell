//
// Created by Ali Yagmur on 3/23/23.
//

#include "../minishell.h"

static char	*get_current_word(char *s, int *a)
{
	int	i;
	char *new;

	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a])
		&& s[*a] != '|')
	{
		i++;
		*a = *a + 1;
	}
	new = malloc(sizeof(char) * i + 1);
	*a = *a - i;
	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a])
		&& s[*a] != '|')
	{
		new[i++] = s[*a];
		*a = *a + 1;
	}
	new[i] = '\0';
	return (new);
}

static bool	set_args(char *line, t_cmds *cmds, int *i)
{
	int	a;

	a = 0;
	cmds->args = malloc(sizeof(char *) * 10);
	while (line[*i] && line[*i] != '|')
	{
		cmds->args[a] = get_current_word(line, i);
		a++;
		while(line[*i] && line[*i] == ' ')
			*i = *i + 1;
	}
	return (true);
}

static bool	set_cmd(char *line, t_cmds *cmds, int *i)
{
	int size;

	size = 0;
	while(line[*i + size] && line[*i + size] != ' '
		&& !is_redir_char(line[*i + size]))
		size++;
	if (size == 0)
	{
		cmds->cmd = NULL;
		return (true);
	}
	cmds->cmd = malloc(sizeof(char) * size);
	if (!cmds->cmd)
		return (false);
	size = 0;
	while(line[*i + size] && line[*i + size] != ' '
		&& !is_redir_char(line[*i + size]))
	{
		cmds->cmd[size] = line[*i + size];
		size++;
	}
	*i += size;
	return (true);
}

static void connect_struct(t_cmds *new)
{
	t_cmds *end;

	if (!g_ms.cmds_f)
	{
		g_ms.cmds_f = new;
		new->next = 0;
	}
	else
	{
		end = g_ms.cmds_f;
		while (end->next)
			end = end->next;
		end->next = new;
		new->next = 0;
	}
}

bool	main_parsing(char *line, t_t_i ti)
{
	struct s_cmds *cmds;
	int i;

	i = 0;
	while(line[i])
	{
		cmds = malloc(sizeof(struct s_cmds));
		set_cmd(line, cmds, &i);
		while(line[i] && line[i] == ' ')
			i++;
		set_args(line, cmds, &i);
		while(line[i] && (line[i] == ' ' || line[i] == '|'))
			i++;
		connect_struct(cmds);
		g_ms.cmd_nbr++;
	}
	parc_struct_tester(g_ms.cmds_f);
	return (true);
}
