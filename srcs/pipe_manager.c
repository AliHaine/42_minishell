/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:47:26 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/23 16:15:21 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_exec(int pipes[][2], char *cmds, t_t_i ti)
{
	if (ti.a == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds);
	}
	else if (ti.a == (g_ms.cmd_nbr - 1))
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds);
	}
	else
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds);
	}
}

static void	pipe_brain2(t_t_i ti, int *pid, t_cmds *cmds, int pipes[][2])
{
	if (ti.a == (ti.c - 1))
	{
		if (pid[ti.a] == 0)
		{
			if (cmds->w == 0)
				p_exec(pipes, cmds->line, ti);
			else
				redirection_main(pipes, cmds, ti);
		}
		close(pipes[ti.a - 1][0]);
	}
	else
	{
		if (pid[ti.a] == 0)
		{
			if (cmds->w == 0)
				p_exec(pipes, cmds->line, ti);
			else
				redirection_main(pipes, cmds, ti);
		}
		close(pipes[ti.a - 1][0]);
		close(pipes[ti.a][1]);
	}
}

static bool	pipe_brain(t_t_i ti, pid_t *pid)
{
	int				pipes[19][2];
	struct s_cmds	*cmds;
	int				r;

	cmds = g_ms.cmds_f;
	pipe_init(pipes, ti.c - 1);
	while (cmds)
	{
		pid[ti.a] = fork();
		if (pid[ti.a] == -1)
			return (false);
		if (ti.a == 0)
		{
			if (pid[ti.a] == 0)
			{
				if (cmds->w == 0)
					p_exec(pipes, cmds->line, ti);
				else
					redirection_main(pipes, cmds, ti);
			}
			close(pipes[0][1]);
		}
		else
			pipe_brain2(ti, pid, cmds, pipes);
		cmds = cmds->next;
		waitpid(pid[ti.a], &r, WIFEXITED(pid[ti.a]));
		g_ms.stat = WEXITSTATUS(r);
		ti.a++;
	}
	return (true);
}

bool	pipe_main(void)
{
	struct s_three_int	ti;
	pid_t				pid[20];

	init_three_int(&ti);
	if (check_all_quote(g_ms.cmds_f) == false)
	{
		printf("minishell: erreur de quote\n");
		return (false);
	}
	ti.c = g_ms.cmd_nbr;
	pipe_brain(ti, pid);
	return (true);
}
