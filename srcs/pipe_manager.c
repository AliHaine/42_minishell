/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:47:26 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/03 18:21:18 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	p_exec(int pipes[][2], t_cmds *cmd, t_t_i ti, t_env *l)
{
	if (ti.a == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_all_pipes(pipes);
		check_all_cmd(cmd, l);
	}
	else if (ti.a == (g_ms.cmd_nbr - 1))
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		close_all_pipes(pipes);
		check_all_cmd(cmd, l);
	}
	else
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes);
		check_all_cmd(cmd, l);
	}
}

static bool	execv_helper(t_t_i ti, t_cmds *cmds, int pipes[][2], t_env *l)
{
	if (!is_unused(cmds))
		return (false);
	if (cmds->w == 0)
		p_exec(pipes, cmds, ti, l);
	else
		redirection_main(pipes, cmds, ti, l);
	return (true);
}

static bool	pipe_brain2(int *pid, t_helper h, int pipes[][2], t_env *l)
{
	if (h.ti.a == (h.ti.c - 1))
	{
		if (pid[h.ti.a] == 0)
			if (!execv_helper(h.ti, h.t_c, pipes, l))
				return (false);
		close(pipes[h.ti.a - 1][0]);
	}
	else
	{
		if (pid[h.ti.a] == 0)
			if (!execv_helper(h.ti, h.t_c, pipes, l))
				return (false);
		close(pipes[h.ti.a - 1][0]);
		close(pipes[h.ti.a][1]);
	}
	return (true);
}

static bool	pipe_brain(pid_t *pid, t_helper h, t_env *l)
{
	int				pipes[19][2];
	int				r;

	pipe_init(pipes);
	while (h.t_c)
	{
		pid[h.ti.a] = fork();
		if (pid[h.ti.a] == -1)
			return (false);
		if (h.ti.a == 0)
		{
			if (pid[h.ti.a] == 0)
				if (!execv_helper(h.ti, h.t_c, pipes, l))
					return (false);
			close(pipes[0][1]);
		}
		else
			if (!pipe_brain2(pid, h, pipes, l))
				return (false);
		h.t_c = h.t_c->next;
		g_ms.stat = WEXITSTATUS(r);
		h.ti.a++;
	}
	return (true);
}

bool	pipe_main(t_env *list)
{
	struct s_three_int	ti;
	pid_t				pid[20];
	int					r;
	t_helper			h;

	init_three_int(&ti);
	h.t_c = g_ms.cmds_f;
	h.ti = ti;
	ti.c = g_ms.cmd_nbr;
	pipe_brain(pid, h, list);
	while (ti.a < ti.c)
	{
		waitpid(pid[ti.a], &r, WIFEXITED(pid[ti.a]));
		ti.a++;
	}
	return (true);
}
