/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   very_little_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:31:36 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 01:19:27 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_three_int(struct s_three_int *ti)
{
	ti->a = 0;
	ti->b = 0;
	ti->c = 0;
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (true);
	return (false);
}

void	add_env_var(t_env **lst, char *path)
{
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	ft_lstadd_back(lst, (*lst)->data);
	free((*lst)->data);
	(*lst)->data = ft_strdup(path);
	ft_lst_back(lst);
}