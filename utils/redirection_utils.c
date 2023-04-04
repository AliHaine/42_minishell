/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:06:20 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:06:22 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_waiting_helper(char **tab, t_helper h)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (h.t_c->args[0] && ft_strcmp(h.t_c->args[0], "-e"))
			printf("%s$\n", tab[i++]);
		else
			printf("%s\n", tab[i++]);
	}
}

void	origin_four_start(t_helper h, int pipes[][2], t_env *l, int fd)
{
	if (h.ti.a != g_ms.cmd_nbr - 1)
		dup2(pipes[h.ti.a][1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close_all_pipes(pipes);
	close(fd);
	check_all_cmd(h.t_c, l);
}

void	redir_main_helper(t_helper h, int pipes[][2], t_t_i ti2, t_env *l)
{
	if (g_ms.cmd_nbr > 1 && h.t_c->next)
		r_exec(pipes, h, ti2.b, l);
	else
		r_exec_single(h, ti2.b, 0, l);
}

void	create_and_close(char *name, int mode)
{
	int	fd;

	if (mode == 3)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, P1 | P2 | S_IRWXO);
	else
		fd = open(name, O_CREAT | O_RDWR, P1 | P2 | S_IRWXO);
	close(fd);
}

void	write_to_file(int fd, char **s)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (s[b] && !is_redir_char(s[b][0]))
	{
		while (s[b][i])
			write(fd, &s[b][i++], 1);
		write(fd, " ", 1);
		b++;
		i = 0;
	}
	write(fd, "\n", 1);
}
