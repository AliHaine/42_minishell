/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/22 17:31:41 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(t_cmds *cmd, char **env)
{
	int		in_q;
	int		i;
	char 	**args;

	i = 0;
	args = ft_split(cmd->cmd_args, ' ');
	while (g_ms.bash[i])
		execve(ft_join(g_ms.bash[i++], cmd->cmd), args, NULL);
	i = -1;
	printf("%s: ", gde());
	/*while (args[0][++i])
		if (!update(args[0][i], &in_q))
			printf("%c", args[0][i]);*/
	printf(": command not found\n");
	check_cmd_is_right(127);
	return (0);
}
