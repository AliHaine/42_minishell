/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:04:14 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:04:16 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_unused(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (cmds->cmd)
		return (true);
	while (cmds->args[i] && !is_redir_char(cmds->args[i][0]))
		i++;
	if (get_origine(cmds->args[i]) == 1)
		return (true);
	return (false);
}

/*bool	pipe_init(int pipes[][2])
{
	int	i;

	i = 0;
	while (i < 19)
	{
		if (pipe(pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}*/

/*void	close_all_pipes(int pipes[][2])
{
	int	i;

	i = 0;
	while (i < 19)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}*/

bool	pipe_init(int pipes[3][2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (pipe(pipes[i]) == -1)
			return (false);
		i++;
	}
	return (true);
}

void	close_all_pipes(int pipes[3][2])
{
	int	i;

	i = 0;
	while(i < 3)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
