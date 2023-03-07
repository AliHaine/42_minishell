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

	if (pid == -1)
		return (false);
	else if (pid == 0)
	{
		printf("fils %s\n", cmds->cmd);
		exit(1);
	}
	else
	{
		printf("parent %s\n", cmds->cmd);
	}
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
	int test = 0;
	int status;
	int cmd_nbr = get_nbr_of_cmds(ms->cmds_f);
	char testc[10];
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
			if (i == 0)
			{
				printf("Fils 0\n");
				test++;
				snprintf(testc, 10, "%d", test);
				close(pipes[i][0]);
				write(pipes[i][1], testc, strlen(testc) + 1);
				close(pipes[i][1]);
			}
			else
			{
				printf("Fils %d\n", i);
				close(pipes[i][0]);
				read(pipes[i - 1][0], testc, strlen(testc) + 1);
				test = atoi(testc);
				test++;
				snprintf(testc, 10, "%d", test);
				write(pipes[i][1], testc, strlen(testc) + 1);
				close(pipes[i][1]);
			}
			exit(0);
		}
		i++;
		cmds = cmds->next;
	}
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

	printf("Pere fin %s, %d/\n", testc, i);
	read(pipes[i - 1][0], testc, strlen(testc) + 1);
	printf("Pere fin %s, %d/\n", testc, i);
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