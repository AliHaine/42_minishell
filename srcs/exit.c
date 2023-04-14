/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:35:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/07 17:15:22 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit //

char	*converte_line(char *line)
{
	char	*newline;
	int		i;
	int		j;
	int		in_q;
	int		in_q2;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (update(line[i], &in_q))
			j++;
	}
	newline = malloc(sizeof(char) * j + 1);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (update(line[i], &in_q2))
			newline[j++] = line[i];
	}
	newline[j] = '\0';
	return (newline);
}

static int	select_exit_num(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	newline = converte_line(line);
	while (line[i])
	{
		if (line[0] == '-' || line[0] == '+')
			i++;
		if (line[i] >= '0' && line[i] <= '9')
			i++;
		else
			return (1);
	}
	g_ms.stat = ft_atoi(line);
	free(newline);
	return (0);
}

// check + 2 arg + isalnum

int	check_exit(t_cmds *cmd)
{
	int		i;

	i = 0;
	if (cmd->args[0] != NULL)
	{
		if (select_exit_num(cmd->args[0]) == 1)
			printf("exit: %s: numeric argument required\n", cmd->args[0]);
	}
	if (cmd->args[0] != NULL && cmd->args[1] != NULL)
	{
		printf("exit: too many arguments\n");
		g_ms.stat = 1;
	}
	g_ms.exit = -1;
	return (0);
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
	{
		free(copy);
		copy = ft_substr(histo, 0, (size_t) i);
	}
	return (copy);
}
