//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

static void	set_cmds_to_struct(char *all_cmds, struct s_three_int ti, struct s_minishell *ms, int head)
{
	struct s_cmds	*cmds;

	cmds = malloc(sizeof(struct s_cmds));
	if (!cmds)
		exit(1);
	ms->cmds_f = cmds;
	while (all_cmds[ti.a])
	{
		ti.c = get_allstr_word_size(all_cmds + ti.a);
		if (head == 0)
		{
			if (!first_words_node(cmds, all_cmds + ti.a, ti.c))
				exit(1);
		}
		else
		{
			if (!new_words_node(cmds, all_cmds + ti.a, ti.c))
				exit(1);
		}
		ti.a += ti.c;
		while (all_cmds[ti.a] && (is_space(all_cmds[ti.a]) || is_pipe_or_et(all_cmds[ti.a])))
			ti.a++;
		head++;
	}
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];
	struct s_three_int ti;

	init_three_int(&ti);
	if (check_all_pipe_cmds(cmds, ti) > 0)
	{
		init_three_int(&ti);
		set_cmds_to_struct(cmds, ti, ms, 0);
		if (check_all_quote(ms->cmds_f) == false)
		{
			printf("minishell: erreur de quote\n");
			return (false);
		}
		check_all_cmd(cmds, ms->env, ms);
		free_words_struct(ms->cmds_f);
		return (true);
	}
	else
		printf("minishell: erreur de commande\n");
	return (false);
}