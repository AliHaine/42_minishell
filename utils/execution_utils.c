/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:14:57 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/12 02:15:00 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**convert_args(t_cmds *cmd)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * size_tab(cmd->args) + 1);
	while (cmd->args[i])
	{
		new[i] = new_line(cmd->args[i]);
		free(cmd->args[i]);
		i++;
	}
	new[i] = NULL;
	i = -1;
	while (new[++i])
		cmd->args[i] = ft_strdup(new[i]);
	return (new);
}

char	**convert_args_env(t_cmds *cmd, t_env *lst)
{
	char	**new;
	char	**env;
	int		i;

	i = 0;
	env = copy_with_lst(lst);
	new = malloc(sizeof(char *) * size_tab(cmd->args) + 1);
	while (cmd->args[i])
	{
		new[i] = env_conversion(cmd->args[i], env, -1, 0);
		i++;
	}
	new[i] = NULL;
	i = -1;
	while (new[++i])
		cmd->args[i] = ft_strdup(new[i]);
	free_tt(env);
	return (new);
}

void	exec_setup(t_pipe *pipes, t_env *l)
{
	pipes->pid = malloc(sizeof(pid_t) * 1);
	pipes->pid[0] = 0;
	init_three_int(&pipes->ti);
	pipe_init(pipes->pipefd);
	pipes->l = l;
}
