/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:10:23 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/03 17:51:08 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_waiting(char *word)
{
	char	*b;
	int		i;
	int		size;
	char	*tab[50];

	i = 0;
	while (1)
	{
		b = readline("> ");
		size = ft_strlen(b);
		tab[i] = malloc(sizeof(char) * size + 1);
		tab[i][size] = '\n';
		tab[i][size + 1] = '\0';
		if (ft_strcmp(b, word))
			break ;
		i++;
	}
	exit(1);
}

static void	r_exec2(int pipes[][2], t_t_i ti, t_cmds *cmd, int fd, t_env *l)
{
	dup2(pipes[ti.a - 1][0], STDIN_FILENO);
	dup2(pipes[ti.a][1], STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(cmd, l);
	dup2(fd, STDIN_FILENO);
	go_to_end_of_file(fd);
	check_all_cmd(cmd, l);
}

static void	r_exec(int pipes[][2], t_cmds *cmd, t_t_i ti, int origin, t_env *l)
{
	int		fd;

	fd = 0;
	while (cmd->args[ti.b])
		ti.b++;
	ti.b--;
	while (!is_redir_char(cmd->args[ti.b][0]))
		ti.b--;
	if (origin != 2)
		fd = open(cmd->args[ti.b + 1], O_RDWR);
	if (origin == 3)
		write_to_file(fd, cmd->args[0]);
	else if (origin == 4)
	{
		if (ti.a != g_ms.cmd_nbr - 1)
			dup2(pipes[ti.a][1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close_all_pipes(pipes);
		close(fd);
		check_all_cmd(cmd, l);
	}
	else if (origin == 1)
		r_exec2(pipes, ti, cmd, fd, l);
	else if (origin == 2)
		exec_waiting(cmd->args[ti.b + 1]);
	close(fd);
	exit(1);
}

static void	r_exec_single(t_cmds *cmd, t_t_i ti, int origin, int fd, t_env *l)
{
	while (cmd->args[ti.b])
		ti.b++;
	ti.b--;
	while (!is_redir_char(cmd->args[ti.b][0]))
		ti.b--;
	if (origin != 2)
		fd = open(cmd->args[ti.b + 1], O_RDWR);
	if (origin == 3)
		write_to_file(fd, cmd->args[0]);
	else if (origin == 4)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		check_all_cmd(cmd, l);
	}
	else if (origin == 1)
	{
		go_to_end_of_file(fd);
		write_to_file(fd, cmd->args[0]);
	}
	else if (origin == 2)
		exec_waiting(cmd->args[ti.b + 1]);
	close(fd);
	exit(1);
}

void	redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti, t_env *l)
{
	t_t_i	ti2;

	init_three_int(&ti2);
	while (cmd->args[ti2.a] && ti2.c != cmd->w)
	{
		if (is_redir_char(cmd->args[ti2.a][0]))
		{
			ti2.b = get_origine(cmd->args[ti2.a]);
			if (ti2.b == 2)
			{
				if (g_ms.cmd_nbr > 1 && cmd->next)
					r_exec(pipes, cmd, ti, ti2.b, l);
				else
					r_exec_single(cmd, ti, ti2.b, 0, l);
			}
			else if (ti2.b == 3 || ti2.b == 1)
				create_and_close(cmd->args[ti2.a + 1]);
			ti2.c++;
		}
		ti2.a++;
	}
	if (!pipes)
		r_exec_single(cmd, ti, ti2.b, 0, l);
	else
		r_exec(pipes, cmd, ti, ti2.b, l);
}
