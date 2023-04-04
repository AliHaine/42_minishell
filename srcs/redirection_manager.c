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

static void	exec_waiting(t_helper h, char *word, bool mode)
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
		tab[i] = b;
		if (ft_strcmp(b, word))
			break ;
		tab[i][size] = '\0';
		i++;
	}
	tab[i] = 0;
	if (ft_strcmp(h.t_c->cmd, "cat") && mode > 0)
		exec_waiting_helper(tab, h);
	exit(1);
}

static void	r_exec2(int pipes[][2], t_helper h, int fd, t_env *l)
{
	dup2(pipes[h.ti.a - 1][0], STDIN_FILENO);
	dup2(pipes[h.ti.a][1], STDOUT_FILENO);
	close_all_pipes(pipes);
	check_all_cmd(h.t_c, l);
	dup2(fd, STDIN_FILENO);
	go_to_end_of_file(fd);
	check_all_cmd(h.t_c, l);
}

void	r_exec(int pipes[][2], t_helper h, int origin, t_env *l)
{
	int		fd;

	fd = 0;
	while (h.t_c->args[h.ti.b])
		h.ti.b++;
	h.ti.b--;
	while (!is_redir_char(h.t_c->args[h.ti.b][0]))
		h.ti.b--;
	if (origin != 2)
		fd = open(h.t_c->args[h.ti.b + 1], O_RDWR);
	if (origin == 3)
		write_to_file(fd, h.t_c->args);
	else if (origin == 4)
		origin_four_start(h, pipes, l, fd);
	else if (origin == 1)
		r_exec2(pipes, h, fd, l);
	else if (origin == 2)
		exec_waiting(h, h.t_c->args[h.ti.b + 1], 0);
	close(fd);
	exit(1);
}

void	r_exec_single(t_helper h, int origin, int fd, t_env *l)
{
	while (h.t_c->args[h.ti.b])
		h.ti.b++;
	h.ti.b--;
	while (!is_redir_char(h.t_c->args[h.ti.b][0]))
		h.ti.b--;
	if (origin != 2)
		fd = open(h.t_c->args[h.ti.b + 1], O_RDWR);
	if (origin == 3)
		write_to_file(fd, h.t_c->args);
	else if (origin == 4)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		check_all_cmd(h.t_c, l);
	}
	else if (origin == 1)
	{
		go_to_end_of_file(fd);
		write_to_file(fd, h.t_c->args);
	}
	else if (origin == 2)
		exec_waiting(h, h.t_c->args[h.ti.b + 1], 1);
	close(fd);
	exit(1);
}

void	redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti, t_env *l)
{
	t_t_i		ti2;
	t_helper	h;

	init_three_int(&ti2);
	h.ti = ti;
	h.t_c = cmd;
	while (cmd->args[ti2.a] && ti2.c != cmd->w)
	{
		if (is_redir_char(cmd->args[ti2.a][0]))
		{
			ti2.b = get_origine(cmd->args[ti2.a]);
			if (ti2.b == 2)
				redir_main_helper(h, pipes, ti2, l);
			else if (ti2.b == 3 || ti2.b == 1)
				create_and_close(cmd->args[ti2.a + 1], ti2.b);
			ti2.c++;
		}
		ti2.a++;
	}
	if (!pipes)
		r_exec_single(h, ti2.b, 0, l);
	else
		r_exec(pipes, h, ti2.b, l);
}
