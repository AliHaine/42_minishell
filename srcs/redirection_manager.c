//
// Created by Ali Yagmur on 3/9/23.
//

#include "../minishell.h"

static bool	r_exec(int pipes[][2], t_cmds *cmds, t_t_i ti)
{
	/*int		fd;
	char	*b;

	//printf("la //%s// //%s//\n", cmd_arg[0], cmd_arg[1]);
	if (cmds->w == 3)
	{
		fd = open(cmd_arg[1], O_RDWR);
		if (fd < 0)
			printf("Error file\n");
		dup2(fd, STDIN_FILENO);
		write_to_file(fd, cmd_arg[0]);
		close(fd);
		exit(1);
	}
	else if (cmds->w == 4)
	{
		if (ti.a != g_ms.cmd_nbr - 1)
			dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds->line);
	}
	else if (cmds->w == 1)
	{
		fd = open(cmd_arg[1], O_RDWR);
		if (fd < 0)
			printf("Error file\n");
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds->line);
		dup2(fd, STDIN_FILENO);
		go_to_end_of_file(fd);
		write_to_file(fd, cmd_arg[0]);
		close(fd);
		exit(1);
	}
	else if (cmds->w == 2)
	{
		if (ti.a != 0)
			dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		while (1)
		{
			b = readline("> ");
			if (ft_strcmp(b, cmd_arg[1]))
			{
				close_all_pipes(pipes, (ti.c - 1));
				exit(0);
			}
			if (ti.a != g_ms.cmd_nbr - 1)
			{
				ft_putstr(b, pipes[ti.a][1]);
				write(pipes[ti.a][1], "\n", 1);
			}
			else
			{
				ft_putstr(b, 1);
				write(1, "\n", 1);
			}
		}
	}*/
	return (true);
}

bool	redirection_main(int pipes[][2], t_cmds *cmds, t_t_i ti)
{
	//ft_split_redir(cmds, cmds->w);
	/*if (!cmd_arg)
		printf("error redir split\n");*/
	r_exec(pipes, cmds, ti);
	//printf("//%s// //%s//\n", cmd_arg[0], cmd_arg[1]);
	//check redir type

	return (true);
}