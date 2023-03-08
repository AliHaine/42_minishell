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

static bool pipe_executor(int *pipes, char *cmds, int i, struct s_minishell *ms)
{
    char *path;
    char **args;

    path = get_cmds_path(cmds);
    args = get_args_cmds(cmds);
    if (!path)
        return (false);
    if (i == 0)
    {
        close(pipes[0]);
        dup2(pipes[1], STDOUT_FILENO);
        if (get_cmd_pipe(cmds) > 0)
            check_all_cmd(cmds, ms->env, ms);
        else
            execve(path, args, ms->env);
        close(pipes[1]);
    }
    else
    {
        if (get_cmd_pipe(cmds) > 0)
        {
            close(pipes[0]);
            dup2(pipes[1], STDOUT_FILENO);
            check_all_cmd(cmds, ms->env, ms);
            close(pipes[1]);
        }
        else
        {
            /*
            close(pipes[0]);
            dup2(pipes[0], STDIN_FILENO);
            read(pipes[0], stash, ft_strlen(stash) + 1);
            test = atoi(testc);
            test++;
            snprintf(testc, 10, "%d", test);
            write(pipes[1], testc, strlen(testc) + 1);
            close(pipes[1]);*/
        }
    }
    exit(0);
}


static bool pipe_brain(struct s_minishell *ms) {
    int i;
    int status;
    int cmd_nbr = get_nbr_of_cmds(ms->cmds_f);
    int pipes[cmd_nbr - 1][2];
    pid_t pid[cmd_nbr - 1];
    struct s_cmds *cmds;

    cmds = ms->cmds_f;
    i = 0;
    pipe_init(pipes, cmd_nbr);
    while (cmds->next)
    {
        pid[i] = fork();
        if (pid[i] == -1)
            return (false);
        if (pid[i] == 0)
        {
            pipe_executor(pipes[i], cmds->cmd, i, ms);
        }
        i++;
        cmds = cmds->next;
    }
    // Ignore les trucs en dessous pour l'instant
    i = 0;
    while (i < (cmd_nbr - 1))
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            printf("Le processus fils %d s'est terminé avec succès.\n", pid[i]);
        } else {
            printf("Le processus fils %d s'est terminé avec une erreur.\n", pid[i]);
        }
        i++;
    }

    //Derniere commande
    if (get_cmd_pipe(cmds->cmd) > 0)
        check_all_cmd(cmds->cmd, ms->env, ms);
    return (true);
}

bool pipe_main(struct s_minishell *ms, char *cmds) {
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