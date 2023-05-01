/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_manger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 23:32:00 by ayagmur           #+#    #+#             */
/*   Updated: 2023/05/01 00:09:26 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	exec_redir_cmd(t_pipe *pipes, t_cmds *cmd)
{
	t_t_i	ti;

	init_three_int(&ti);
	while (cmd->args[ti.a] && ti.c != cmd->w)
	{
		if (is_redir_char(cmd->args[ti.a][0]))
		{
			ti.b = get_origine(cmd->args[ti.a]);
			if (ti.b == 2 || ti.b == 4)
				stdin_redirection(ti.b, cmd->args[ti.a + 1], cmd->cmd);
			else if (ti.b == 3 || ti.b == 1)
				stdou_redirection(ti.b, cmd->args[ti.a + 1]);
			ti.c++;
		}
		ti.a++;
	}
	close_all_pipes(pipes->pipefd);
	check_all_cmd(cmd, pipes->l);
	return (true);
}

static void	kids_execution(t_cmds *cmd, t_pipe *pipes)
{
	if (cmd->next)
		dup2(pipes->pipefd[(pipes->ti.a % 3)][1], STDOUT_FILENO);
	if (pipes->ti.a > 2)
	{
		if (pipes->ti.a % 3 == 0)
			dup2(pipes->pipefd[2][0], STDIN_FILENO);
		else
			dup2(pipes->pipefd[(pipes->ti.a % 3) - 1][0], STDIN_FILENO);
	}
	else if (pipes->ti.a > 0)
		dup2(pipes->pipefd[((pipes->ti.a % 3) - 1)][0], STDIN_FILENO);
	if (cmd->w > 0)
		exec_redir_cmd(pipes, cmd);
	else
	{
		close_all_pipes(pipes->pipefd);
		if (cmd->sep == 3)
			dup2(g_ms.def_dup, STDOUT_FILENO);
		check_all_cmd(cmd, pipes->l);
	}
}

static bool	exec_manager(t_pipe *pipes, t_cmds *cmd)
{
	while (cmd)
	{
		if (pipes->ti.a > 2)
			pipe(pipes->pipefd[(pipes->ti.a % 3)]);
		pid_tab_growth(pipes, pipes->ti.a);
		pipes->pid[pipes->ti.a] = fork();
		if (pipes->pid[pipes->ti.a] == 0)
			kids_execution(cmd, pipes);
		if (pipes->ti.a > 0)
			close(pipes->pipefd[((pipes->ti.a % 3) - 1)][0]);
		if (cmd->next)
			close(pipes->pipefd[((pipes->ti.a % 3))][1]);
		cmd = cmd->next;
		pipes->ti.a++;
	}
	return (true);
}

bool	exec_main(t_env *l)
{
	t_pipe		p;
	t_cmds		*cmd;

	cmd = g_ms.cmds_f;
	if (try_our_basical(cmd))
	{
		check_all_cmd(cmd, l);
		return (true);
	}
	exec_setup(&p, l);
	exec_manager(&p, cmd);
	while (p.pid[p.ti.b])
	{
		waitpid(p.pid[p.ti.b], &p.ti.c, WIFEXITED(p.pid[p.ti.b]));
		p.ti.b++;
		g_ms.stat = WEXITSTATUS(p.ti.c);
	}
	free(p.pid);
	return (true);
}
