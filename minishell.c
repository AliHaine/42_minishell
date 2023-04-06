/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:11:27 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/04 03:29:38 by mbouaza          ###   ########.fr       */
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

static bool	single_cmd_exec(t_t_i ti, t_env *list)
{
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
		single_fork(cmd, ti, list);
	return (true);
}

static int	run_process(char *line, t_env *list)
{
	struct s_three_int	ti;
	char				*new;
	char				**env;

	env = copy_with_lst(list);
	new = env_conversion(line, env, -1, 0);
	free_tt(env);
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
		single_cmd_exec(ti, list);
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

static bool	main_struct_init(char **env)
{
	g_ms.histo_fd = open(".history", O_CREAT | O_RDWR, P1 | P2 | S_IRWXO);
	g_ms.stat = 0;
	g_ms.old = 0;
	g_ms.env = env;
	if (g_ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (false);
	}
	g_ms.exit = 1;
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*list;

	(void)argc;
	(void)argv;
	signal_main();
	main_struct_init(env);
	if (main_struct_init(env) == false)
		return (1);
	list = lst_copy_tab(env);
	go_to_end_of_file(g_ms.histo_fd);
	main_process(list);
	close(g_ms.histo_fd);
	free_tt(g_ms.bash);
	free_list(&list);
	exit(g_ms.stat);
}
