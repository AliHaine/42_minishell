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

static bool	pipe_brain2(t_t_i ti, int *pid, t_cmds *cmds, int pipes[][2], t_env *l)
{
	if (ti.a == (ti.c - 1))
	{
		if (pid[ti.a] == 0)
			if (!execv_helper(ti, cmds, pipes, l))
				return (false);
		close(pipes[ti.a - 1][0]);
	}
	else
	{
		if (pid[ti.a] == 0)
			if (!execv_helper(ti, cmds, pipes, l))
				return (false);
		close(pipes[ti.a - 1][0]);
		close(pipes[ti.a][1]);
	}
	return (true);
}

static bool	pipe_brain(t_t_i ti, pid_t *pid, t_cmds *cmds, t_env *l)
{
	int				pipes[19][2];
	int				r;

	pipe_init(pipes);
	while (cmds)
	{
		pid[ti.a] = fork();
		if (pid[ti.a] == -1)
			return (false);
		if (ti.a == 0)
		{
			if (pid[ti.a] == 0)
				if (!execv_helper(ti, cmds, pipes, l))
					return (false);
			close(pipes[0][1]);
		}
		else
			if (!pipe_brain2(ti, pid, cmds, pipes, l))
				return (false);
		cmds = cmds->next;
		g_ms.stat = WEXITSTATUS(r);
		ti.a++;
	}
	return (true);
}

bool	pipe_main(t_env *list)
{
	struct s_three_int	ti;
	pid_t				pid[20];
	int					r;
	t_cmds				*cmds;

	init_three_int(&ti);
	cmds = g_ms.cmds_f;
	/*if (check_all_quote(g_ms.cmds_f, 0, 0) == false)
	{
		printf("minishell: erreur de quote\n");
		return (false);
	}*/
	ti.c = g_ms.cmd_nbr;
	pipe_brain(ti, pid, cmds, list);
	while (ti.a < ti.c)
	{
		waitpid(pid[ti.a], &r, WIFEXITED(pid[ti.a]));
		ti.a++;
	}
	return (true);
}
