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

bool	is_blank(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_space(str[i]))
			size++;
		i++;
	}
	if (size == 0)
		return (true);
	return (false);
}

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

int	get_allstr_word_size(char *str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		if (str[size] == '|' || str[size] == '&')
		{
			break ;
		}
		size++;
	}
	if (!str[size])
		return (size);
	return (size - 1);
}

bool	is_redir_char(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}
