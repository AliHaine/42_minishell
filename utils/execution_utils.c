//
// Created by Ali Yagmur on 4/7/23.
//
#include "../minishell.h"

bool	pid_tab_growth(t_pipe *pipes, int size)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * (size + 2));
	while (size > 0)
	{
		pid[i] = pipes->pid[i];
		i++;
		size--;
	}
	pid[size + 1] = 0;
	free(pipes->pid);
	pipes->pid = pid;
	return (true);
}

bool	pid_tab_remove_last(t_pipe *pipes)
{
	int		i;
	int		max;
	pid_t	*pid;

	max = 0;
	i = 0;
	while (pipes->pid[max++]);
	pid = malloc(sizeof(pid_t) * max);
	while (i < (max - 1))
	{
		pid[i] = pipes->pid[i];
		i++;
	}
	pid[i] = 0;
	free(pipes->pid);
	pipes->pid = pid;
	return (true);
}

void	exec_setup(t_pipe *pipes, t_env *l)
{
	pipes->pid = malloc(sizeof(pid_t) * 1);
	pipes->pid[0] = 0;
	init_three_int(&pipes->ti);
	pipe_init(pipes->pipefd);
	pipes->l = l;
}

// return new line without quot

char	*new_line(char *arg)
{
	int		i;
	int		x;
	int		in_q;
	char	*new;

	i = 0;
	x = 0;
	while (arg[i])
	{
		if (!update(arg[i], &in_q))
			x++;
		i++;
	}
	i = -1;
	new = malloc(sizeof(char) * x + 1);
	x = 0;
	while (arg[++i])
	{
		if (!update(arg[i], &in_q))
			new[x++] = arg[i];
	}
	new[x] = '\0';
	return (new);
}