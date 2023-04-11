/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/11 18:13:20 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **path_ex(char **env)
{
	char	**bash;
	char	*path;

	path = ft_getenv(env, "PATH");
	bash = ft_split(path, ':');
	free(path);
	return (bash);
}

static void	ft_execve2(char **args, char **env)
{
	int		i;
	int		in_q;
	char	*gdee;

	i = -1;
	gdee = gde();
	execve(args[0], args, env);
	printf("%s: ", gdee);
	free(gdee);
	while (args[0][++i])
		if (!update(args[0][i], &in_q))
			printf("%s", args[0][i]);
	printf(": command not found\n");
	check_cmd_is_right(127);
	free_tt(args);
}

int	ft_execve(t_cmds *cmd, t_env *lst)
{
	char	**args;
	char	**bash;
	char	*join;
	char 	**env;

	env = copy_with_lst(lst);
	/*
	cmd->cmd_args = convert_args(cmd);
	cmd->args = convert_args_env(cmd, l);
	*/
	args = ft_split(cmd->cmd_args, ' ');
	bash = path_ex(env);
	while (*bash)
	{
		join = ft_join(*bash++, args[0]);
		execve(join, args, env);
		free(join);
	}
	ft_execve2(args, env);
	free_tt(env);
	exit(127);
	return (0);
}
