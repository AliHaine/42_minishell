/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 17:02:41 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update(char c, int *in_q)
{
	if (c == '\'' && *in_q != 2)
	{
		*in_q = 1 - (1 * (*in_q == 1));
		return (1);
	}
	if (c == '\"' && *in_q != 1)
	{
		*in_q = 2 - (2 * (*in_q == 2));
		return (1);
	}
	return (0);
}

// var //

static int	*size_quote(char *s, int i)
{
	int	*tab;
	int	in_q;

	tab = malloc(sizeof(int) * 2);
	tab[0] = i;
	tab[1] = i;
	while (tab[0] > 0)
	{
		if ((s[tab[0]] == '\'' || s[tab[0]] == '\"'))
		{
			while (tab[0] > 0 && (s[tab[0]] == '\'' || s[tab[0]] == '\"'))
				tab[0]--;
			break ;
		}
		tab[0]--;
	}
	if (tab[0] == 0)
		tab[0] = i;
	while (s[tab[1]])
	{
		if (s[tab[1]] == '\'' || s[tab[1]] == '\"')
		{
			while (s[tab[1]] && (s[tab[1]] == '\'' || s[tab[1]] == '\"'))
				tab[1]++;
			tab[1] -= tab[0] + 1;
			break ;
		}
		tab[1]++;
	}
	return (tab);
}

static int	count_q(char *s, int i)
{
	int	quote;

	quote = 0;
	while (i > 0)
	{
		if (s[i] == '\'')
			quote++;
		i--;
	}
	if (quote % 2 != 0)
		return (0);
	return (1);
}

static int	quote_count(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 2;
	while (str[++i])
	{
		if (str[i] == '\'')
			quote++;
	}
	return (quote);
}

static int	update_2(char *s, int *in_q)
{
	int	i;

	i = 0;
	if (s[i] && s[i] == '\'' && *in_q != 2)
		*in_q = 1 - (1 * (*in_q == 1));
	else if (s[i] && s[i] == '\"' && *in_q != 1)
		*in_q = 2 - (2 * (*in_q == 2));
	while (s[i + 1])
	{
		if (s[i + 1] == '\'' && *in_q != 2)
			*in_q = 1 - (1 * (*in_q == 1)); 
		else if (s[i + 1] == '\"' && *in_q != 1)
			*in_q = 2 - (2 * (*in_q == 2));
		i++;
	}
	if (s[i] == '\'' && *in_q != 2)
		return (1);
	return (0);
}

int var_c(char *s, int i)
{
	int *size;
	char *str;
	int in_q;
	
	size = size_quote(s, i);
	str = ft_substr(s, size[0] + 1, size[1]);
	if (update_2(str, &in_q) == 1 && quote_count(str) % 2 == 0
		&& count_q(s, i) == 0)
	{
		if (size)
			free(size);
		return (1);
	}
	if (size)
		free(size);
	return (0);
}
