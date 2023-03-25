/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:16:59 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/18 15:17:01 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_origine(char *cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i] == '>' && cmds[i + 1] == '>')
			return (1);
		else if (cmds[i] == '<' && cmds[i + 1] == '<')
			return (2);
		else if (cmds[i] == '>')
			return (3);
		else if (cmds[i] == '<')
			return (4);
		i++;
	}
	return (0);
}

bool	is_redir_char(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}
