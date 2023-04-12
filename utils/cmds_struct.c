/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:14:29 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 00:45:39 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	connect_struct(t_cmds *new)
{
	t_cmds	*end;

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

void	free_words_struct(struct s_cmds *cmds)
{
	struct s_cmds	*to_free;

	to_free = cmds;
	while (to_free)
	{
		cmds = to_free->next;
		if (to_free->cmd)
			free(to_free->cmd);
		if (to_free->cmd_args)
			free(to_free->cmd_args);
		free_tt(to_free->args);
		free(to_free);
		to_free = cmds;
	}
	g_ms.cmds_f = 0;
	g_ms.cmd_nbr = 0;
}