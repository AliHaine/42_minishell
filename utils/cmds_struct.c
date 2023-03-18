/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:14:29 by ayagmur           #+#    #+#             */
/*   Updated: 2023/03/18 15:14:30 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_nbr_of_cmds(struct s_cmds *cmds)
{
	int				size;
	struct s_cmds	*iterator;

	size = 0;
	iterator = cmds;
	while (iterator)
	{
		iterator = iterator->next;
		size++;
	}
	return (size);
}

bool	first_words_node(struct s_cmds *cmds, char *str, int size)
{
	int	i;

	cmds->cmd = malloc(sizeof(char) * size + 1);
	if (!cmds->cmd)
		return (false);
	i = str_copy(cmds->cmd, str, size);
	cmds->w = get_origine(str + i);
	cmds->next = 0;
	cmds->prev = 0;
	return (true);
}

bool	new_words_node(struct s_cmds *cmds, char *str, int size)
{
	int				i;
	struct s_cmds	*new;

	while (cmds->next)
		cmds = cmds->next;
	new = malloc(sizeof(t_cmds));
	if (!new)
	{
		return (false);
	}
	cmds->next = new;
	new->next = 0;
	new->prev = cmds;
	new->cmd = malloc(sizeof(char) * size + 1);
	if (!new->cmd)
		return (false);
	i = str_copy(new->cmd, str, size);
	new->w = get_origine(str + i);
	return (1);
}

void	free_words_struct(struct s_cmds *cmds)
{
	struct s_cmds	*to_free;

	to_free = cmds;
	while (to_free->prev)
		to_free = to_free->prev;
	while (to_free)
	{
		cmds = to_free->next;
		free(to_free->cmd);
		free(to_free);
		to_free = cmds;
	}
}

void	parc_struct_tester(struct s_cmds *cmds)
{
	struct s_cmds	*ite;

	ite = cmds;
	while (ite)
	{
		printf("Cmd = %s W = %d\n", ite->cmd, ite->w);
		ite = ite->next;
	}
}
