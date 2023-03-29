/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:56:12 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/29 11:50:39 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	set_args(char *line, t_cmds *cmds, int *i)
{
	int	a;
	int	aw;

	a = 0;
	cmds->args = malloc(sizeof(char *) * 50);
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
	a = 0;
	while (cmds->args[a])
	{
		if (is_redir_char(cmds->args[a][0]))
			cmds->w++;
		a++;
	}
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
	cmds->cmd = malloc(sizeof(char) * size + 1);
	if (!cmds->cmd)
		return (false);
	size = 0;
	while (line[*i + size] && line[*i + size] != ' '
		&& !is_redir_char(line[*i + size]))
	{
		cmds->cmd[size] = line[*i + size];
		size++;
	}
	cmds->cmd[size] = '\0';
	*i += size;
	return (true);
}

static bool	set_cmd_args_pipe(t_cmds *cmd, int b)
{
	cmd->cmd_args = ft_strdup(cmd->cmd);
	while (cmd->args[b])
	{
		if (!is_redir_char(cmd->args[b][0]))
			cmd->cmd_args = ft_strjoin_parse(cmd->cmd_args, cmd->args[b]);
		else
			break ;
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
		cmds->cmd_args = 0;
		if (cmds->cmd)
			set_cmd_args_pipe(cmds, 0);
		connect_struct(cmds);
		if (check_error_redir(cmds) == false)
			return (false);
		g_ms.cmd_nbr++;
	}
	return (true);
}
