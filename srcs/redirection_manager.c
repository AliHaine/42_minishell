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

static void	exec_waiting(char *word)
{
	char 	*b;
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

static bool	r_exec(int pipes[][2], t_cmds *cmd, t_t_i ti, int origin)
{
	int		fd;
	char	*b;
	char	*file;

	while (cmd->args[ti.b])
		ti.b++;
	ti.b--;
	while (!is_redir_char(cmd->args[ti.b][0]))
		ti.b--;
	if (origin == 3)
	{
		fd = open(cmd->args[ti.b + 1], O_RDWR);
		write_to_file(fd, cmd->args[0]);
		close(fd);
		exit(1);
	}
	else if (origin == 4)
	{
		fd = open(cmd->args[ti.b + 1], O_RDWR);
		if (ti.a != g_ms.cmd_nbr - 1)
			dup2(pipes[ti.a][1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close_all_pipes(pipes);
		close(fd);
		check_all_cmd(cmd);
	}
	else if (origin == 1)
	{
		fd = open(cmd->args[ti.b], O_RDWR);
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes);
		check_all_cmd(cmd);
		dup2(fd, STDIN_FILENO);
		go_to_end_of_file(fd);
		check_all_cmd(cmd);
		//write_to_file(fd, cmd_arg[0]);
		close(fd);
		exit(1);
	}
	else if (origin == 2)
	{
		exec_waiting(cmd->args[ti.b + 1]);
	}
	return (true);
}

static bool	r_exec_single(t_cmds *cmd, t_t_i ti, int origin)
{
	int		fd;
	char	*gnl;

	printf("single enter\n");
	while (cmd->args[ti.b])
		ti.b++;
	ti.b--;
	while (!is_redir_char(cmd->args[ti.b][0]))
		ti.b--;
	if (origin == 3)
	{
		fd = open(cmd->args[ti.b + 1], O_RDWR);
		write_to_file(fd, cmd->args[0]);
		close(fd);
		exit(1);
	}
	else if (origin == 4)
	{
		fd = open(cmd->args[ti.b + 1], O_RDWR);
		dup2(fd, STDIN_FILENO);
		close(fd);
		//execve("/bin/cat", args, NULL);

		check_all_cmd(cmd);
	}
	else if (origin == 1)
	{
		fd = open(cmd->args[ti.b + 1], O_RDWR);
		go_to_end_of_file(fd);
		write_to_file(fd, cmd->args[0]);
		close(fd);
		exit(1);
	}
	else if (origin == 2)
	{
		exec_waiting(cmd->args[ti.b + 1]);
	}
	return (true);
}

bool	redirection_main(int pipes[][2], t_cmds *cmd, t_t_i ti)
{
	int	i;
	int ret;
	int	size;
	int	fd;

	i = 0;
	size = 0;
	parc_struct_tester(g_ms.cmds_f);
	while (cmd->args[i] && size != cmd->w)
	{
		if (is_redir_char(cmd->args[i][0]))
		{
			ret = get_origine(cmd->args[i]);
			if (ret == 2)
			{
				if (g_ms.cmd_nbr > 1 && cmd->next)
					r_exec(pipes, cmd, ti, ret);
				else
					r_exec_single(cmd, ti, ret);
			}
			else if (ret == 3 || ret == 1)
			{
				fd = open(cmd->args[i + 1], O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, O_RDWR);
				close(fd);
			}
			size++;
		}
		i++;
	}
	if (!pipes)
	{
		r_exec_single(cmd, ti, ret);
	}
	else
		r_exec(pipes, cmd, ti, ret);
	return (true);
}
