/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:47:26 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/18 14:47:28 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_cmds_to_struct(char *a_c, t_t_i ti, t_minishell *ms, int h)
{
	struct s_cmds	*cmds;

	cmds = malloc(sizeof(struct s_cmds));
	if (!cmds)
		exit(1);
	ms->cmds_f = cmds;
	while (a_c[ti.a])
	{
		ti.c = get_allstr_word_size(a_c + ti.a);
		if (h == 0)
		{
			if (!first_words_node(cmds, a_c + ti.a, ti.c))
				exit(1);
		}
		else
		{
			if (!new_words_node(cmds, a_c + ti.a, ti.c))
				exit(1);
		}
		ti.a += ti.c;
		while (a_c[ti.a] && (is_space(a_c[ti.a]) || is_pipe_or_et(a_c[ti.a])))
			ti.a++;
		h++;
	}
}

static void	p_exec(int pipes[][2], char *cmds, t_t_i ti, t_minishell *ms)
{
	if (ti.a == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds, ms);
	}
	else if (ti.a == get_nbr_of_cmds(ms->cmds_f) - 1)
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds, ms);
	}
	else
	{
		dup2(pipes[ti.a - 1][0], STDIN_FILENO);
		dup2(pipes[ti.a][1], STDOUT_FILENO);
		close_all_pipes(pipes, (ti.c - 1));
		check_all_cmd(cmds, ms);
	}
}

static bool	pipe_brain(t_minishell *ms, t_t_i ti, pid_t *pid)
{
	int				pipes[19][2];
	struct s_cmds	*cmds;

	cmds = ms->cmds_f;
	pipe_init(pipes, ti.c - 1);
	while (cmds)
	{
		pid[ti.a] = fork();
		if (pid[ti.a] == -1)
			return (false);
		if (ti.a == 0)
		{
			if (pid[ti.a] == 0)
				p_exec(pipes, cmds->cmd, ti, ms);
			close(pipes[0][1]);
		}
		else if (ti.a == (ti.c - 1))
		{
			if (pid[ti.a] == 0)
				p_exec(pipes, cmds->cmd, ti, ms);
			close(pipes[ti.a - 1][0]);
		}
		else
		{
			if (pid[ti.a] == 0)
				p_exec(pipes, cmds->cmd, ti, ms);
			close(pipes[ti.a - 1][0]);
			close(pipes[ti.a][1]);
		}
		cmds = cmds->next;
		ti.a++;
	}
	return (true);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	struct s_three_int	ti;
	pid_t				pid[20];

	init_three_int(&ti);
	set_cmds_to_struct(cmds, ti, ms, 0);
	if (check_all_quote(ms->cmds_f) == false)
	{
		printf("minishell: erreur de quote\n");
		return (false);
	}
	init_three_int(&ti);
	ti.c = get_nbr_of_cmds(ms->cmds_f);
	pipe_brain(ms, ti, pid);
	while (ti.a < ti.c)
	{
		waitpid(pid[ti.a], &ti.b, 0);
		ti.a++;
	}
	free_words_struct(ms->cmds_f);
	return (true);
}
