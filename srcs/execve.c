/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/31 02:23:41 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_execve2(char **args)
{
	int		i;
	int		in_q;
	char	*gdee;

	i = -1;
	gdee = gde();
	printf("%s: ", gdee);
	free(gdee);
	while (args[0][++i])
		if (!update(args[0][i], &in_q))
			printf("%c", args[0][i]);
	printf(": command not found\n");
	check_cmd_is_right(127);
	free_tt(args);
}

int	ft_execve(t_cmds *cmd, char **env, int i)
{
	char	**args;
	char	*join;
	char	**bash;
	char	*path;

	path = ft_getenv(env, "PATH");
	bash = ft_split(path, ':');
	free(path);
	args = ft_split(cmd->cmd_args, ' ');
	while (bash[i])
	{
		join = ft_join(bash[i++], cmd->cmd);
		execve(join, args, NULL);
		free(join);
	}
	ft_execve2(args);
	free_tt(bash);
	return (0);
}
