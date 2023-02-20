#include "minishell.h"

bool	sigaction_manager(struct s_minishell *ms)
{
	signal(2, ctrl_c);
	return (true);
}

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

static int	main_process(struct s_minishell *ms)
{
	char *histo;

	while (ms->exit > 0)
	{
		histo = readline("\U0001F1F9\U0001F1F7  >>");
		if (check_validity(histo))
		{
			add_history(histo);
			write_to_histo((char *) histo, ms->histo_fd);
		}
	}
}

int main (int argc, char **argv, char **env)
{
	struct s_minishell ms;

	sigaction_manager(&ms);
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
	return (0);
}