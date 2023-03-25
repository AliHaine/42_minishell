/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:18:12 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:18:13 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_all_quote(struct s_cmds *cmds, int i, int size)
{
	while (cmds)
	{
		while (cmds->cmd_args[size])
			size++;
		while (cmds->cmd_args[i] && cmds->cmd_args[i] != ' ')
			i++;
		i++;
		if (cmds->cmd_args[i] == '\'' || cmds->cmd_args[i] == '"')
		{
			if (cmds->cmd_args[i] == '\'')
			{
				if (cmds->cmd_args[size - 1] != '\'')
					return (false);
			}
			else
				if (cmds->cmd_args[size - 1] != '"')
					return (false);
		}
		i = 0;
		size = 0;
		cmds = cmds->next;
	}
	return (true);
}

bool	check_error_redir(t_cmds *cmd)
{
	t_t_i	ti;
	int		ret;

	init_three_int(&ti);
	while (ti.c != cmd->w && cmd->args[ti.a])
	{
		ti.b = is_redir_char(cmd->args[ti.a][0]);
		if (ti.b > 0)
		{
			if (!cmd->args[ti.a + 1])
				return (false);
			if (get_origine(cmd->args[ti.a]) == 4)
			{
				ret = open(cmd->args[ti.a + 1], O_RDWR);
				if (ret < 0)
					return (false);
				close (ret);
			}
			ti.c++;
		}
		ti.a++;
	}
	return (true);
}
