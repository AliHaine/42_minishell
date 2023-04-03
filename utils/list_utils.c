/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 02:04:04 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/03 18:22:31 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew(char *str)
{
	t_env	*cell;

	cell = malloc(sizeof(t_env));
	if (!cell)
		return (NULL);
	cell->data = ft_strdup(str);
	cell->next = NULL;
	cell->past = NULL;
	return (cell);
}

// go in the last node //

t_env	*ft_lstlast(t_env *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_lstadd_back(t_env **list, char *str)
{
	t_env	*cur;
	t_env	*save_new;

	if (*list == NULL)
		*list = ft_lstnew(str);
	else
	{
		cur = ft_lstlast(*list);
		cur->next = ft_lstnew(str);
		save_new = cur->next;
		save_new->past = cur;
	}
}

// go to the head of list //

void	ft_lst_back(t_env **lst)
{
	if (lst == NULL)
		return ;
	while ((*lst)->past != NULL)
		*lst = (*lst)->past;
}

int	ft_lst_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
