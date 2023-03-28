/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:11:27 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:11:28 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_validity(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			size++;
		i++;
	}
	if (size == 0)
		return (false);
	return (true);
}

static bool	single_cmd_exec(t_t_i ti)
{
	int		pid;
	int		r;
	t_cmds	*cmd;

	cmd = g_ms.cmds_f;
	if (get_cmd(cmd->cmd) == 4 || get_cmd(cmd->cmd) == 5
		|| get_cmd(cmd->cmd) == 6 || get_cmd(cmd->cmd) == 7)
	{
		if (cmd->w == 0)
			check_all_cmd(cmd);
		else
			redirection_main(0, cmd, ti);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->w == 0)
				check_all_cmd(cmd);
			else
				redirection_main(0, cmd, ti);
		}
		waitpid(pid, &r, WIFEXITED(pid));
		g_ms.stat = WEXITSTATUS(r);
	}
	return (true);
}

static int	run_process(char *line)
{
	struct s_three_int	ti;

	init_three_int(&ti);
	if (main_parsing(line) == false)
		return (0);
	if (g_ms.cmd_nbr > 1)
		pipe_main();
	else
		single_cmd_exec(ti);
	return (1);
}

static int	main_process(void)
{
	char				*histo;
	char 				*hh;

	while (g_ms.exit > 0)
	{
		hh = g_d_e();
		histo = readline(hh);
		if (!histo)
			break ;
		free(hh);
		if (check_validity(histo))
		{
			hh = histo_pars(histo);
			add_history(hh);
			write_to_histo(hh, g_ms.histo_fd);
			free(hh);
		}
		if (check_is_empty(histo) == 0 || check_exit(histo) == 0)
			continue ;
		run_process(histo);
		free(histo);
		free_words_struct(g_ms.cmds_f);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	signal(2, (void *)ctrl_c);
	signal(SIGQUIT, (void *)ctrl_bs);
	rl_catch_signals = 0;
	g_ms.histo_fd = open(".history", O_RDWR);
	g_ms.stat = 0;
	if (g_ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (1);
	}
	g_ms.env = env;
	g_ms.bash = ft_split(ft_getenv(env, "PATH"), ':');
	g_ms.exit = 1;
	go_to_end_of_file(g_ms.histo_fd);
	main_process();
	close(g_ms.histo_fd);
	free_tt(g_ms.bash);
	exit(g_ms.stat);
}
