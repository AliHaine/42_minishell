#include "minishell.h"

static bool	check_validity(char *str)
{
	int i;
	int size;

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

static int	main_process(struct s_minishell *ms, char **env)
{
	char *histo;
	int pid;

	while (ms->exit > 0)
	{
		histo = readline(g_d_e());
		if (!histo)
			break;
		if (check_validity(histo))
		{
			add_history(histo_pars(histo));
			write_to_histo(histo_pars(histo), ms->histo_fd);
		}
		if (is_contain_pipe(histo))
			pipe_main(ms, histo);
		else
		{
			pid = fork();
			if (pid == 0)
				check_all_cmd(histo, ms);
			wait(0);
		}
	}
	return (1);
}

int main (int argc, char **argv, char **env)
{
	struct s_minishell ms;

	signal(2, ctrl_c);
	rl_catch_signals = 0;
	ms.histo_fd =  open(".history", O_RDWR);
	if (ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (1);
	}
	ms.env = env;
	ms.exit = 1;
	go_to_end_of_file(ms.histo_fd);
	main_process(&ms, env);
	free_tt(ms.env);
	close(ms.histo_fd);
	return (0);
}