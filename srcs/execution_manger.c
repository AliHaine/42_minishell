//
// Created by Ali Yagmur on 4/7/23.
//

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

static bool	try_our_basical(t_cmds *cmd)
{
	if (get_cmd(cmd->cmd) == 5 || get_cmd(cmd->cmd) == 6
		|| get_cmd(cmd->cmd) == 7 || get_cmd(cmd->cmd) == 8
		|| get_cmd(cmd->cmd) == 4)
		return (true);
	return (false);
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
		check_all_cmd(cmd, pipes->l);
	}
}

static bool	exec_manager(t_pipe *pipes, t_env *l, t_cmds *cmd)
{
	int exit_status;

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
		if (cmd->sep > 1)
		{
			waitpid(pipes->pid[pipes->ti.a], &exit_status, 0);
			pid_tab_remove_last(pipes);
		}
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
	exec_manager(&p, l, cmd);
	while (p.pid[p.ti.b])
	{
		waitpid(p.pid[p.ti.b], &p.ti.c, WIFEXITED(p.pid[p.ti.b]));
		p.ti.b++;
	}
	return (true);
}
