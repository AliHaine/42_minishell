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
}

bool	is_last_enter(int i, t_cmds *cmd)
{
	int	origin;

	while (cmd[i])
	{
		if (is_redir_char(cmd->args[i][0]))
		{
			origin = get_origine(cmd->args[i]);
			if (origin == 2 || origin = 4)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_last_out(char **args)
{
	int	origin;
	int	i

	i = 0;
	while (args[i])
	{
		if (is_redir_char(args[i][0]))
		{
			origin = get_origine(args[i]);
			if (origin == 1 || origin = 3)
				return (false);
		}
		i++;
	}
	return (true);
}*/