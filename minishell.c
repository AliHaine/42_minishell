#include "minishell.h"

bool	sigaction_manager(struct s_minishell *ms)
{
	signal(2, ctrl_c);
	return (true);
}

static int	main_process(struct s_minishell *ms)
{
	char *histo;

	while (ms->exit > 0)
	{
		histo = readline("\U0001F1F9\U0001F1F7  >> ");
		if (!histo)
			break;
		if (!is_blank(histo))
		{
			pipe_main(ms, histo);
			add_history(histo);
			write_to_histo((char *) histo, ms->histo_fd);
		}
		if (pipe_main(ms, histo) == true)
			check_all_cmd(histo);
	}
	return (1);
}

int main (int argc, char **argv, char **env)
{
	struct s_minishell ms;

	sigaction_manager(&ms);
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
	main_process(&ms);
	close(ms.histo_fd);
	return (0);
}