/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/29 11:01:10 by mbouaza          ###   ########.fr       */
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

int	ft_execve(t_cmds *cmd, char **env)
{
	int		i;
	char	**args;
	char	*join;

	i = 0;
	args = ft_split(cmd->cmd_args, ' ');
	while (g_ms.bash[i])
	{
		join = ft_join(g_ms.bash[i++], cmd->cmd);
		execve(join, args, NULL);
		free(join);
	}
	ft_execve2(args);
	return (0);
}
