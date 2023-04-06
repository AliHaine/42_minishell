/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/03 16:36:26 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_execve2(char **args)
{
	int		i;
	int		in_q;
	char	*gdee;

	i = -1;
	execve(args[0], args, g_ms.env);
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

int	ft_execve(t_cmds *cmd)
{
	char	**args;
	char	**bash;
	char	*join;
	char	*path;

	args = ft_split(cmd->cmd_args, ' ');
	path = ft_getenv(g_ms.env, "PATH");
	bash = ft_split(path, ':');
	while (*bash)
	{
		join = ft_join(*bash++, args[0]);
		execve(join, args, g_ms.env);
		free(join);
	}
	ft_execve2(args);
	exit(127);
	return (0);
}
