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

void	set_cmds_to_struct(char *a_c, t_t_i ti, int h)
{
	struct s_cmds	*cmds;

	cmds = malloc(sizeof(struct s_cmds));
	if (!cmds)
		exit(1);
	g_ms.cmds_f = cmds;
	while (a_c[ti.a])
	{
		ti.c = get_allstr_word_size(a_c + ti.a);
		if (h == 0)
		{
			if (!first_words_node(cmds, a_c + ti.a, ti.c))
				exit(1);
		}
		else
		{
			if (!new_words_node(cmds, a_c + ti.a, ti.c))
				exit(1);
		}
		ti.a += ti.c;
		while (a_c[ti.a] && (is_space(a_c[ti.a]) || is_pipe_or_et(a_c[ti.a])))
			ti.a++;
		h++;
		g_ms.cmd_nbr++;
	}
}

bool	first_words_node(struct s_cmds *cmds, char *str, int size)
{
	cmds->line = malloc(sizeof(char) * size + 1);
	if (!cmds->line)
		return (false);
	str_copy(cmds->line, str, size);
	cmds->w = get_origine(cmds->line);
	cmds->next = 0;
	cmds->prev = 0;
	return (true);
}

bool	new_words_node(struct s_cmds *cmds, char *str, int size)
{
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
	new->line = malloc(sizeof(char) * size + 1);
	if (!new->line)
		return (false);
	str_copy(new->line, str, size);
	new->w = get_origine(new->line);
	return (1);
}

void	free_words_struct(struct s_cmds *cmds)
{
	struct s_cmds	*to_free;

	to_free = cmds;
	while (to_free)
	{
		cmds = to_free->next;
		free(to_free->line);
		free(to_free);
		to_free = cmds;
	}
	g_ms.cmd_nbr = 0;
}

void	parc_struct_tester(struct s_cmds *cmds)
{
	struct s_cmds	*ite;

	ite = cmds;
	while (ite)
	{
		printf("Cmd = %s W = %d\n", ite->line, ite->w);
		ite = ite->next;
	}
}
