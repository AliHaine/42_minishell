//
// Created by Ali Yagmur on 4/7/23.
//
#include "../minishell.h"

/*void	exec_first_dup(int p, t_cmds *cmd, t_env *l)
{
	dup2(p, STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
}

void	exec_last_dup(int p, t_cmds *cmd, t_env *l)
{
	dup2(p, STDIN_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
}

void	exec_middle_dup(int p1, int p2, t_cmds *cmd, t_env *l)
{
	dup2(p1, STDIN_FILENO);
	dup2(p2, STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
} */

/*bool pid_tab_growth(t_pipe *pipes, int val)
{
	int	size;
	int	i;
	pid_t  *pid;

	size = 0;
	i = 0;
	while (pipes->pid[size])
		size++;
	if (size == 0)
		size = 1;
	else if (size == 1)
		size = 2;
	pid = malloc(sizeof(pid_t) * (size + 1));
	while (pipes->pid[i])
	{
		pid[i] = pipes->pid[i];
		i++;
	}
	pid[i++] = val;
	pid[i] = 0;
	free(pipes->pid);
	pipes->pid = pid;
	return (true);
}*/