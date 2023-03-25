/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:56:12 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 13:56:13 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		while (line[*i] && line[*i] == ' ')
			*i = *i + 1;
	}
	cmds->args[a] = NULL;
	return (true);
}

static bool	set_cmd(char *line, t_cmds *cmds, int *i)
{
	int	size;

	size = 0;
	while (line[*i + size] && line[*i + size] != ' '
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
	while (line[*i + size] && line[*i + size] != ' '
		&& !is_redir_char(line[*i + size]))
	{
		cmds->cmd[size] = line[*i + size];
		size++;
	}
	*i += size;
	return (true);
}

static bool	set_cmd_args(t_cmds *cmd, int b)
{
	if (!cmd->cmd)
	{
		if (is_redir_char(cmd->args[0][0]))
		{
			if (cmd->args[1])
				cmd->cmd_args = ft_strdup(cmd->args[1]);
			else
				return (cmd->cmd_args = NULL);
			cmd->w++;
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
		else
			cmd->w++;
		b++;
	}
	return (true);
}

bool	main_parsing(char *line)
{
	struct s_cmds	*cmds;
	int				i;

	i = 0;
	while (line[i])
	{
		cmds = malloc(sizeof(struct s_cmds));
		if (!cmds)
			printf("error\n");
		cmds->w = 0;
		set_cmd(line, cmds, &i);
		while (line[i] && line[i] == ' ')
			i++;
		set_args(line, cmds, &i);
		while (line[i] && (line[i] == ' ' || line[i] == '|'))
			i++;
		if (cmds->cmd)
			cmds->cmd_args = ft_strdup(cmds->cmd);
		set_cmd_args(cmds, 0);
		connect_struct(cmds);
		g_ms.cmd_nbr++;
	}
	return (true);
}
