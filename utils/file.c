/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:07:46 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/25 14:07:48 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_to_end_of_file(int fd)
{
	char	*str;

	str = get_next_line(fd);
	if (!str)
		return ;
	while (str)
	{
		add_history(histo_pars(str));
		free(str);
		str = get_next_line(fd);
	}
	free(str);
}

bool	write_to_histo(char *str, int fd)
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
