/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:07:46 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/16 12:02:56 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_to_end_of_file(int fd)
{
	char	*str;
	char	*hh;

	str = get_next_line(fd);
	if (!str)
		return ;
	while (str)
	{
		hh = histo_pars(str);
		if (!hh)
			return ;
		add_history(hh);
		free(str);
		free(hh);
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	free(str);
}

static bool	write_to_histo(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	return (true);
}

void	histo_main(char *histo)
{
	char	*hh;

	hh = histo_pars(histo);
	add_history(hh);
	write_to_histo(hh, g_ms.histo_fd);
	free(hh);
}
