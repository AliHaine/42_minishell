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

void	create_and_close(char *name)
{
	int	fd;

	fd = open(name, O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, O_RDWR);
	close(fd);
}

void	write_to_file(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
