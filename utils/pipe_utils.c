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

bool	pipe_init(int pipes[][2])
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
}

void	close_all_pipes(int pipes[][2])
{
	int	i;

	i = 0;
	while (i < 19)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
