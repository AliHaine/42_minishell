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

static int	main_process(void)
{
	char *histo;
	int pid;

	while (g_ms.exit > 0)
	{
		histo = readline(g_d_e());
		if (!histo)
			break;
		if (check_validity(histo))
		{
			add_history(histo_pars(histo));
			write_to_histo(histo_pars(histo), g_ms.histo_fd);
		}
		if (is_contain_pipe(histo))
			pipe_main(histo);
		else
		{
			pid = fork();
			if (pid == 0)
				check_all_cmd(histo);
			wait(0);
		}
	}
	return (1);
}

int main (int argc, char **argv, char **env)
{
	signal(2, (void *)ctrl_c);
	rl_catch_signals = 0;
	g_ms.histo_fd =  open(".history", O_RDWR);
	g_ms.stat = 0;
	if (g_ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (1);
	}
	g_ms.env = env;
	g_ms.exit = 1;
	go_to_end_of_file(g_ms.histo_fd);
	main_process();
	free_tt(g_ms.env);
	close(g_ms.histo_fd);
	return (0);
}