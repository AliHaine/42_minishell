//
// Created by Ali Yagmur on 3/23/23.
//

#include "../minishell.h"

static bool	set_args(char *line, t_cmds *cmds, int *i)
{
	int	a;

	a = 0;
	cmds->args = malloc(sizeof(char *) * 10);
	if (!cmds->args)
		return (false);
	while (line[*i] && line[*i] != '|')
	{
		cmds->args[a] = get_current_word(line, i);
		a++;
		while(line[*i] && line[*i] == ' ')
			*i = *i + 1;
	}
	cmds->args[a] = NULL;
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

static bool	set_cmd_args(t_cmds *cmd)
{
	int b;

	b = 0;
	if (cmd->cmd)
		cmd->cmd_args = ft_strdup(cmd->cmd);
	else
	{
		if (is_redir_char(cmd->args[0][0]))
		{
			if (cmd->args[1])
				cmd->cmd_args = ft_strdup(cmd->args[1]);
			else
			{
				cmd->cmd_args = NULL;
				return (false);
			}
			b++;
		}
		else
			cmd->cmd_args = ft_strdup(cmd->args[0]);
		b++;
	}
	while (cmd->args[b])
	{
		if (!is_redir_char(cmd->args[b][0]))
			cmd->cmd_args = ft_strjoin_parse(cmd->cmd_args, cmd->args[b]);
		b++;
	}
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

bool	main_parsing(char *line)
{
	struct s_cmds *cmds;
	int i;

	i = 0;
	while(line[i])
	{
		cmds = malloc(sizeof(struct s_cmds));
		if(!cmds)
			printf("error\n");
		set_cmd(line, cmds, &i);
		while (line[i] && line[i] == ' ')
			i++;
		set_args(line, cmds, &i);
		while (line[i] && (line[i] == ' ' || line[i] == '|'))
			i++;
		set_cmd_args(cmds);
		connect_struct(cmds);
		g_ms.cmd_nbr++;
	}
	return (true);
}
