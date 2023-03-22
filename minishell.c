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

static int run_process(char *line)
{
	int					pid;
	struct s_three_int	ti;

	init_three_int(&ti);
	set_cmds_to_struct(line, ti, 0);
	if (is_contain_pipe(line))
		pipe_main();
	else
	{
		if (get_cmd(line) == 4 || get_cmd(line) == 5
			|| get_cmd(line) == 6)
			check_all_cmd(line);
		else
		{
			pid = fork();
			if (pid == 0)
				check_all_cmd(line);
			wait(0);
		}
	}
	free(line);
	free_words_struct(g_ms.cmds_f);
	return (1);
}

static int	main_process(void)
{
	char				*histo;

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
		if (check_is_empty(histo) == 0 || check_exit(histo) == 0)
			continue ;
		run_process(histo);
	}
	return (1);
}

int main (int argc, char **argv, char **env)
{
	signal(2, (void *)ctrl_c);
	signal(SIGQUIT, (void *)ctrl_bs);
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
	close(g_ms.histo_fd);
	return (0);
}