//
// Created by Ali Yagmur on 3/9/23.
//

#include "../minishell.h"

static bool	r_exec(int pipes[][2], t_cmds *cmds, t_t_i ti, char **cmd_arg)
{
	int fd;

	fd = open(cmd_arg[1], O_RDWR);
	if (fd < 0)
		printf("Error file\n");
	if (cmds->w == 3)
	{
		dup2(fd, STDIN_FILENO);
		write_to_file(fd, cmd_arg[0]);
		exit(1);
	}
	else if (cmds->w == 4)
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		if (ti.a != get_nbr_of_cmds(g_ms.cmds_f) - 1)
			dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds->cmd);
	}
	else if (cmds->w == 1)
	{
		dup2(fd, STDIN_FILENO);
		go_to_end_of_file(fd);
		write_to_file(fd, cmd_arg[0]);
		exit(1);
	}
	return (true);
}

bool	redirection_main(int pipes[][2], t_cmds *cmds, t_t_i ti)
{
	char **cmd_arg;

	cmd_arg = ft_split_redir(cmds->cmd, cmds->w);
	if (!cmd_arg)
		printf("error redir split\n");
	r_exec(pipes, cmds, ti, cmd_arg);
	//printf("//%s// //%s//\n", cmd_arg[0], cmd_arg[1]);
	//check redir type

	return (true);
}