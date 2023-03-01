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
	cmds = ms->cmds_f;
	while (cmds)
	{
		cmds = cmds->next;
	}
}

static int	check_all_pipe_cmds(char *cmds, struct s_three_int *ti)
{
	char *str;

	while (cmds[ti->a])
	{
		while (cmds[ti->a + ti->b] && !is_space(cmds[ti->a + ti->b]))
			ti->b++;
		str = ft_substr(cmds, ti->a, ti->b);
		if (get_cmd(str) == 0)
			return (free_str_rzero(str));
		free(str);
		while (cmds[ti->a])
		{
			if (cmds[ti->a] == '|')
			{
				if (cmds[ti->a + 1] == '|')
					ti->a++;
				ti->a += 2;
				ti->c++;
				break;
			}
			ti->a++;
		}
		ti->b = 0;
	}
	return (ti->c += 1);
}

bool	pipe_main(struct s_minishell *ms, char *cmds)
{
	int pipefd[2];
	struct s_three_int ti;

	init_three_int(&ti);
	if (check_all_pipe_cmds(cmds, &ti) > 0)
	{
		printf("ici\n");
		init_three_int(&ti);
		set_cmds_to_struct(cmds, ti, ms, 0);
		check_all_cmd(cmds, ms->env, ms);
		free_words_struct(ms->cmds_f);
		return (true);
	}
	else
		printf("minishell: command not found\n");

	return (false);
}