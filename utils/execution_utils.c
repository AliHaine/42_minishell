//
// Created by Ali Yagmur on 4/7/23.
//
#include "../minishell.h"

void	exec_single_dup(int pipes[2], t_cmds *cmd, t_env *l)
{
	dup2(pipes[1], STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
}

void	exec_last_dup(int pipes[2], t_cmds *cmd, t_env *l)
{
	dup2(pipes[0], STDIN_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
}

void	exec_middle_dup(int pipes1[2], int pipes2[2] t_cmds *cmd, t_env *l)
{
	dup2(pipes1[0], STDIN_FILENO);
	dup2(pipes2[1], STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
}