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
    while (i < size) {
        if (pipe(pipes[i]) == -1)
            return (false);
        i++;
    }
    return (true);
}

static bool pipe_executor(int pipes[][2], char *cmds, int i, struct s_minishell *ms)
{
	if (i == 0)
    {
        dup2(pipes[i][1], STDOUT_FILENO);
        close(pipes[i][1]);
		close(pipes[i][0]);
		check_all_cmd(cmds, ms);
    }
	else if (i == get_nbr_of_cmds(ms->cmds_f) - 1)
    {
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		check_all_cmd(cmds, ms);
    }
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		close(pipes[i][0]);
		close(pipes[i][1]);
		check_all_cmd(cmds, ms);
	}
	return (true);
}


static bool pipe_brain(struct s_minishell *ms) {
    int i;
    int status;
    int cmd_nbr = get_nbr_of_cmds(ms->cmds_f);
    int pipes[cmd_nbr - 1][2];
    pid_t pid[cmd_nbr];
    struct s_cmds *cmds;

    cmds = ms->cmds_f;
    i = 0;
    pipe_init(pipes, cmd_nbr);
    while (cmds)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return (false);
        if (pid[i] == 0)
            pipe_executor(pipes, cmds->cmd, i, ms);
        i++;
        cmds = cmds->next;
    }
    i = 0;
    while (i < cmd_nbr)
    {
		printf("a\n");
        waitpid(pid[i], &status, 0);
        i++;
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
    pipe_brain(ms);
    free_words_struct(ms->cmds_f);
    return (true);
}