/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:35:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/22 17:37:24 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit //

static char *select_exit_num(char *line, int i)
{
	int j;
	char *str;

	j = 0;
	i += 4;
	str = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i + j] && (line[j + i] != ' ' && line[j + i] != '\t'))
		j++;
	str = ft_substr(line, i, j);
	return (str);
}

int	check_exit(char *h)
{
	int	i;
	int j;
	char *num;

	i = 0;
	j = 0;
	num = NULL;
	while (h[i])
	{
		while (h[i] && (h[i] == ' ' || h[i] == '\t'))
			i++;
		if (h[i + 3] && h[i] == 'e' && h[i + 1] == 'x' && h[i + 2] == 'i'
			&& h[i + 3] == 't' && (h[i + 4] == '\0'
				|| h[i + 4] == '\t' || h[i + 4] == ' '))
		{
			num = select_exit_num(h, i);
			g_ms.exit = -1;
			g_ms.stat = ft_atoi(num);
			free(num);
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
	else
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
