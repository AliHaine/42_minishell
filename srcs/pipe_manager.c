//
// Created by Ali Yagmur on 2/22/23.
//
#include "../minishell.h"

static void set_cmds_to_struct(char *all_cmds, struct s_three_int ti, struct s_minishell *ms, int head) {
    struct s_cmds *cmds;

    cmds = malloc(sizeof(struct s_cmds));
    if (!cmds)
        exit(1);
    ms->cmds_f = cmds;
    while (all_cmds[ti.a]) {
        ti.c = get_allstr_word_size(all_cmds + ti.a);
        if (head == 0) {
            if (!first_words_node(cmds, all_cmds + ti.a, ti.c))
                exit(1);
        } else {
            if (!new_words_node(cmds, all_cmds + ti.a, ti.c))
                exit(1);
        }
        ti.a += ti.c;
        while (all_cmds[ti.a] && (is_space(all_cmds[ti.a]) || is_pipe_or_et(all_cmds[ti.a])))
            ti.a++;
        head++;
    }
}

static bool pipe_init(int pipes[][2], int size)
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

static void	close_all_pipes(int pipes[][2], int size)
{
	while (size > 0)
	{
		close(pipes[size - 1][0]);
		close(pipes[size - 1][1]);
		size--;
	}
}

static void	pipe_executor(int pipes[][2], char *cmds, struct s_three_int ti, struct s_minishell *ms)
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

static bool pipe_brain(struct s_minishell *ms, struct s_three_int ti)
{
    int pipes[ti.c - 1][2];
    pid_t pid[ti.c];
    struct s_cmds *cmds;

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
				pipe_executor(pipes, cmds->cmd, ti, ms);
			close(pipes[0][1]);
		}
		else if (ti.a == (ti.c - 1))
		{
			if (pid[ti.a] == 0)
				pipe_executor(pipes, cmds->cmd, ti, ms);
			close(pipes[ti.a - 1][0]);
		}
		else
		{
			if (pid[ti.a] == 0)
				pipe_executor(pipes, cmds->cmd, ti, ms);
			close(pipes[ti.a - 1][0]);
			close(pipes[ti.a][1]);
		}
		cmds = cmds->next;
		ti.a++;
    }
	ti.a = 0;
    while (ti.a < ti.c)
    {
		waitpid(pid[ti.a], &ti.b, 0);
		ti.a++;
    }
    return (true);
}

bool pipe_main(struct s_minishell *ms, char *cmds)
{
    struct s_three_int ti;

    init_three_int(&ti);
    set_cmds_to_struct(cmds, ti, ms, 0);
    if (check_all_quote(ms->cmds_f) == false) {
        printf("minishell: erreur de quote\n");
        return (false);
    }
	init_three_int(&ti);
	ti.c = get_nbr_of_cmds(ms->cmds_f);
    pipe_brain(ms, ti);
    free_words_struct(ms->cmds_f);
    return (true);
}