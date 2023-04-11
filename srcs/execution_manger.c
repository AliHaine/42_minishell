//
// Created by Ali Yagmur on 4/7/23.
//

#include "../minishell.h"

int size_tab(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

// return new line without quot

char *new_line(char *arg)
{
	int i;
	int x;
	int in_q;
	char *new;

	i = 0;
	x = 0;
	while (arg[i])
	{
		if (!update(arg[i], &in_q))
			x++;
		i++;
	}
	i = -1;
	new = malloc(sizeof(char) * x + 1);
	x = 0;
	while (arg[++i])
	{
		if (!update(arg[i], &in_q))
			new[x++] = arg[i];
	}
	new[x] = '\0';
	return (new);
}

char **convert_args(t_cmds *cmd)
{
	char **new;
	int i;

	i = 0;
	new = malloc(sizeof(char *) * size_tab(cmd->args) + 1);
	while (cmd->args[i])
	{
		new[i] = new_line(cmd->args[i]);
		free(cmd->args[i]);
		i++;
	}
	new[i] = NULL;
	i = -1;
	while (new[++i])
		cmd->args[i] = ft_strdup(new[i]);
	
	return (new);
}

char **convert_args_env(t_cmds *cmd, t_env *lst)
{
	char **new;
	char **env;
	int i;

	i = 0;
	env = copy_with_lst(lst);
	new = malloc(sizeof(char *) * size_tab(cmd->args) + 1);
	while (cmd->args[i])
	{
		new[i] = env_conversion(cmd->args[i], env, -1, 0);
		i++;
	}
	new[i] = NULL;
	i = -1;
	while (new[++i])
		cmd->args[i] = ft_strdup(new[i]);
	free_tt(env);
	return (new);
}

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

static void exec_setup(t_pipe *pipes, t_env *l)
{
	/*pipes->pid = malloc(sizeof(pid_t) * 1);
	pipes->pid[0] = 0;*/
	init_three_int(&pipes->ti);
	pipe_init(pipes->pipefd);
	pipes->l = l;
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

bool	exec_manager(t_env *l)
{
	t_pipe 		pipes;
	t_cmds		*cmd;

	cmd = g_ms.cmds_f;
	if (try_our_basical(cmd))
	{
		check_all_cmd(cmd, l);
		return (true);
	}
	exec_setup(&pipes, l);
	// args //
	cmd->args = convert_args(cmd);
	cmd->args = convert_args_env(cmd, l);
	// <<   //
	while (cmd)
	{
		if (pipes.ti.a > 2)
			pipe(pipes.pipefd[(pipes.ti.a % 3)]);
		//pid_tab_growth(&pipes)
		pipes.pid[pipes.ti.a] = fork();
		if (pipes.pid[pipes.ti.a] == 0)
			kids_execution(cmd, &pipes);
		if (pipes.ti.a > 0)
			close(pipes.pipefd[((pipes.ti.a % 3) - 1)][0]);
		if (cmd->next)
			close(pipes.pipefd[((pipes.ti.a % 3))][1]);
		cmd = cmd->next;
		pipes.ti.a++;
	}
	pipes.pid[pipes.ti.a] = 0;
	while (pipes.pid[pipes.ti.b])
	{
		waitpid(pipes.pid[pipes.ti.b], &pipes.ti.c, WIFEXITED(pipes.pid[pipes.ti.b]));
		pipes.ti.b++;
	}
	return (true);
}
