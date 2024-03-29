/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:06:20 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 00:51:48 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_waiting(char *word, int i, int size)
{
	char	*b;
	int		fd;

	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, P1 | P2 | S_IRWXO);
	while (1)
	{
		b = readline("> ");
		write(fd, b, sizeof(char) * ft_strlen(b));
		write(fd, "\n", 1);
		size = ft_strlen(b);
		if (ft_strcmp(b, word))
			break ;
		i++;
	}
	close(fd);
}

void	stdou_redirection(int origin, char *name)
{
	int	fd;

	if (origin == 3)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, P1 | P2 | S_IRWXO);
	else
	{
		fd = open(name, O_CREAT | O_RDWR, P1 | P2 | S_IRWXO);
		go_to_end_of_file(fd);
	}
	dup2(fd, STDOUT_FILENO);
}

void	stdin_redirection(int origin, char *name, char *cmd)
{
	int	fd;

	if (origin == 2)
	{
		exec_waiting(name, 0, 0);
		if (!cmd)
			exit(1);
		fd = open(".heredoc", O_RDONLY, P1 | P2 | S_IRWXO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		fd = open(name, O_RDONLY, P1 | P2 | S_IRWXO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
