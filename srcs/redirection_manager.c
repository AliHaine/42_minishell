/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:10:23 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:10:24 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	r_exec(int pipes[][2], t_cmds *cmd, t_t_i ti)
{
	/*int		fd;
	char	*b;

	//printf("la //%s// //%s//\n", cmd_arg[0], cmd_arg[1]);
	if (cmd->w == 3)
	{
		fd = open(cmd_arg[1], O_CREAT, O_RDWR);
		dup2(fd, STDIN_FILENO);
		check_all_cmd(cmd)
		//write_to_file(fd, cmd_arg[0]);
		close(fd);
		exit(1);
	}
	else if (cmd->w == 4)
	{
		if (ti.a != g_ms.cmd_nbr - 1)
			dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmd->line);
	}
	else if (cmd->w == 1)
	{
		fd = open(cmd_arg[1], O_CREAT, O_RDWR);
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmd->line);
		dup2(fd, STDIN_FILENO);
		go_to_end_of_file(fd);
		check_all_cmd(cmd);
		//write_to_file(fd, cmd_arg[0]);
		close(fd);
		exit(1);
	}
	else if (cmd->w == 2)
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

bool	redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti)
{
	r_exec(pipes, cmd, ti);
	return (true);
}
