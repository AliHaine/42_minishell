/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:35:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 17:05:30 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit //

int	check_exit(char *h)
{
	int	i;

	i = 0;
	while (h[i])
	{
		while (h[i] && (h[i] == ' ' || h[i] == '\t'))
			i++;
		if (h[i + 3] && h[i] == 'e' && h[i + 1] == 'x' && h[i + 2] == 'i'
			&& h[i + 3] == 't' && (h[i + 4] == '\0'
				|| h[i + 4] == '\t' || h[i + 5] == ' '))
		{
			g_ms.exit = -1;
			return (0);
		}
		break ;
	}
	return (1);
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
