/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:11:27 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 01:15:15 by mbouaza          ###   ########.fr       */
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

static int	run_process(char *line, t_env *list)
{
	struct s_three_int	ti;
	char				*new;
	char				**env;

	env = copy_with_lst(list);
	new = env_conversion(line, env, -1, 0);
	new = convert_args3(new);
	free_tt(env);
	init_three_int(&ti);
	g_ms.on_cmd = 1;
	if (main_parsing(new) == false)
	{
		free(new);
		new = NULL;
		return (0);
	}
	free(new);
	exec_main(list);
	return (1);
}

static char *readline_fix(void)
{
	char *histo;
	char	*hh;

	hh = g_d_e();
	histo = readline(hh);
	free(hh);
	return (histo);
}

static int	main_process(t_env *list)
{
	char	*histo;

	while (g_ms.exit > 0)
	{
		g_ms.on_cmd = 0;
		histo = readline_fix();
		if (!histo)
			break ;
		if (check_validity(histo))
			histo_main(histo);
		if (check_is_empty(histo) == 0)
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
