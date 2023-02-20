#include "minishell.h"

bool	sigaction_manager(struct s_minishell *ms)
{
	signal(2, ctrl_c);
	return (true);
}

int main (int argc, char **argv, char **env)
{
	const char *test;
	struct s_minishell ms;

	sigaction_manager(&ms);
	ms.histo_fd =  open(".history", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (ms.histo_fd == -1)
	{
		printf("Error file history\n");
		return (1);
	}
	while (1)
	{
		test = readline("\U0001F1F9\U0001F1F7  >>");
		add_history(test);
		write_to_histo((char *) test, ms.histo_fd);
	}

	return (0);
}