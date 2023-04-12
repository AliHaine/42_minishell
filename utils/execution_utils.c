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
