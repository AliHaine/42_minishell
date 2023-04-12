/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:06:20 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:06:22 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_waiting(char *word)
{
	char	*b;
	int		i;
	int		size;
	char	*tab[50];

	i = 0;
	while (1)
	{
		b = readline("> ");
		size = ft_strlen(b);
		tab[i] = malloc(sizeof(char) * size + 1);
		tab[i] = b;
		if (ft_strcmp(b, word))
			break ;
		tab[i][size] = '\0';
		i++;
	}
	tab[i] = 0;
	exit(1);
}

void	stdou_redirection(int origin, char *name, t_pipe *pipes)
{
	int fd;
	if (origin == 3)
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, P1 | P2 | S_IRWXO);
	else
	{
		fd = open(name, O_CREAT | O_RDWR, P1 | P2 | S_IRWXO);
		go_to_end_of_file(fd);
	}
	(void)pipes;
	dup2(fd, STDOUT_FILENO);
}

void	stdin_redirection(int origin, char *name, t_pipe *pipes)
{
	int	fd;

	(void)pipes;
	if (origin == 2)
		exec_waiting(name);
	else
	{
		fd = open(name, O_RDONLY, P1 | P2 | S_IRWXO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
