//
// Created by Ali Yagmur on 4/7/23.
//

#include "../minishell.h"


static bool exec_redir_cmd(t_pipe *pipes, t_cmds *cmd)
{
	t_t_i	ti;

	init_three_int(&ti);
	while (cmd->args[ti.a] && ti.c != cmd->w)
	{
		if (is_redir_char(cmd->args[ti.a][0]))
		{
			ti.b = get_origine(cmd->args[ti.a]);
			if (ti.b == 2 || ti.b == 4)
				stdin_redirection(ti.b, cmd->args[ti.a + 1], pipes);
			else if (ti.b == 3 || ti.b == 1)
				stdou_redirection(ti.b, cmd->args[ti.a + 1], pipes);
			ti.c++;
		}
		ti.a++;
	}
	close_all_pipes(pipes.pipefd);
	//dup2(pipes->piperedir[1], STDOUT_FILENO);
	check_all_cmd(cmd, pipes->l);
	return (true);
}

/*static bool	exec_pipe_cmd(t_pipe *pipes, t_cmds *cmd)
{
	(void)pipes;
	(void)cmd;

	return (true);
}*/



static void exec_setup(t_pipe *pipes, t_env *l)
{
	/*pipes->pid = malloc(sizeof(pid_t) * 1);
	pipes->pid[0] = 0;*/
	init_three_int(&pipes->ti);
	pipe_init(pipes->pipefd);
	pipes->l = l;
}

bool	exec_manager(t_env *l)
{
	t_pipe 		pipes;
	t_cmds		*cmd;
	int r;

	exec_setup(&pipes, l);
	cmd = g_ms.cmds_f;
	while (cmd)
	{
		if (pipes.ti.a > 3)
			pipe(pipes.pipefd[(pipes.ti.a % 3)]);
		//pid_tab_growth(&pipes)
		pipes.pid[pipes.ti.a] = fork();
		if (pipes.pid[pipes.ti.a] == 0)
		{
			if (cmd->next)
				dup2(pipes.pipefd[(pipes.ti.a % 3)][1], STDOUT_FILENO);
			if (pipes.ti.a > 0)
				dup2(pipes.pipefd[((pipes.ti.a % 3) - 1)][0], STDIN_FILENO);
			if (cmd->w > 0) {
				exec_redir_cmd(&pipes, cmd);
			} else {
				close_all_pipes(pipes.pipefd);
				check_all_cmd(cmd, l);
			}
		}
		if (pipes.ti.a > 0) {
			close(pipes.pipefd[((pipes.ti.a % 3) - 1)][0]);
		}
		if (cmd->next) {
			close(pipes.pipefd[((pipes.ti.a % 3))][1]);
		}
		cmd = cmd->next;
		pipes.ti.a++;
	}
	pipes.pid[pipes.ti.a] = 0;
	while (pipes.pid[pipes.ti.b])
	{
		waitpid(pipes.pid[pipes.ti.b], &r, WIFEXITED(pipes.pid[pipes.ti.b]));
		pipes.ti.b++;
	}
	return (true);
}
