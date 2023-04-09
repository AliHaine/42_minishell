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

bool	exec_manager(t_env *l)
{
	t_pipe 		pipes;
	t_cmds		*cmd;

	pipes.pid = malloc(sizeof(pid_t) * 2);
	init_three_int(&pipes.ti);
	pipe_init(pipes.pipefd);
	pipe(pipes.piperedir);
	pipes.l = l;
	cmd = g_ms.cmds_f;
	while (cmd)
	{
		if (cmd->w > 0)
		{
			printf("if\n");
			exec_redir_cmd(&pipes, cmd);
		}
		else
		{
			printf("else\n");
			pipe_main(l);
		}
		cmd = cmd->next;
		pipes.ti.a++;
	}
	return (true);
}
