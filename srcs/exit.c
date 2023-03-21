/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:35:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 07:30:37 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit //

void	exit_shell(void)
{
	struct s_minishell	*ms;
}

int	check_cmd_is_right(int fd)
{
	if (fd > 0)
	{
		g_ms.stat = fd;
		return (-1);
	}
	g_ms.stat = 0;
	return (0);
}

char	*histo_pars(char *histo)
{
	int		i;
	char	*copy;

	i = ft_strlen(histo) - 1;
	copy = ft_strdup(histo);
	if (!copy)
		return (NULL);
	if (copy[i] && copy[i] == '\n')
		copy[i] = '\0';
	return (copy);
}

void	free_tt(char **str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		free(str[a]);
		a++;
	}
	free(str);
}
