/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:11:27 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/03 17:48:27 by mbouaza          ###   ########.fr       */
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

static bool	single_cmd_exec(t_t_i ti, int pid, t_env *list)
{
	int		r;
	t_cmds	*cmd;

	cmd = g_ms.cmds_f;
	if (get_cmd(cmd->cmd) == 4 || get_cmd(cmd->cmd) == 5
		|| get_cmd(cmd->cmd) == 6 || get_cmd(cmd->cmd) == 7)
	{
		if (cmd->w == 0)
			check_all_cmd(cmd, list);
		else
			redirection_main(0, cmd, ti, list);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->w == 0)
				check_all_cmd(cmd, list);
			else
				redirection_main(0, cmd, ti, list);
		}
		waitpid(pid, &r, WIFEXITED(pid));
		g_ms.stat = WEXITSTATUS(r);
	}
	return (true);
}

static int	run_process(char *line, t_env *list)
{
	struct s_three_int	ti;
	char *new;

	new = env_conversion(line, g_ms.env, -1, 0);
	init_three_int(&ti);
	if (main_parsing(new) == false)
	{
		free(new);
		new = NULL;
		return (0);
	}
	free(new);
	if (g_ms.cmd_nbr > 1)
		pipe_main(list);
	else
		single_cmd_exec(ti, 0, list);
	return (1);
}
 
static int	main_process(t_env *list)
{
	char	*histo;
	char	*hh;

	while (g_ms.exit > 0)
	{
		hh = g_d_e();
		histo = readline(hh);
		if (!histo)
			break ;
		free(hh);
		if (check_validity(histo))
			histo_main(histo);
		if (check_is_empty(histo) == 0 || check_exit(histo) == 0)
		{
			free(histo);
			free_words_struct(g_ms.cmds_f);
			continue ;
		}
		run_process(histo, list);
		free_words_struct(g_ms.cmds_f);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env *list;
		
	signal(2, (void *)ctrl_c);
	signal(SIGQUIT, (void *)ctrl_bs);
	rl_catch_signals = 0;
	g_ms.histo_fd = open(".history", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	g_ms.stat = 0;
	g_ms.old = 0;
	if (g_ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (1);
	}
	list = lst_copy_tab(env); 
	g_ms.exit = 1;
	go_to_end_of_file(g_ms.histo_fd);
	main_process(list);
	close(g_ms.histo_fd);
	free_tt(g_ms.env);
	free_tt(g_ms.bash);
	free_list(&list);
	exit(g_ms.stat);
}
