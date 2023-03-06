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

static bool	new_pipe(struct s_cmds *cmds, int *pipes)
{
	int pid;
	pid = fork();

	//if ()
	return (true);
}

static bool	pipe_init(int pipes[][2], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (pipe(pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

static bool	pipe_executor(struct s_minishell *ms)
{
	int i;
	int pipes[get_nbr_of_cmds(ms->cmds_f) - 1][2];
	struct s_cmds *cmds;

	cmds = ms->cmds_f;
	i = 0;
	pipe_init(pipes, get_nbr_of_cmds(ms->cmds_f));
	while (cmds->next)
	{

		new_pipe(cmds, pipes[i]);
		cmds = cmds->next;
	}
	//le dernier
	return (true);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	struct s_three_int ti;

	//init_three_int(&ti);
	//if (check_all_pipe_cmds(cmds, ti) > 0)

	init_three_int(&ti);
	set_cmds_to_struct(cmds, ti, ms, 0);
	//parc_struct_tester(ms->cmds_f);
	if (check_all_quote(ms->cmds_f) == false)
	{
		printf("minishell: erreur de quote\n");
		return (false);
	}
	pipe_executor(ms);
	//check_all_cmd(cmds, ms->env, ms);
	free_words_struct(ms->cmds_f);
	return (true);

	/*else
		printf("minishell: erreur de commande\n");*/
	return (false);
}