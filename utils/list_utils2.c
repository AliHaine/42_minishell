/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:50:07 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/11 23:44:59 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		free(current->data);
		next = current->next;
		free(current);
		current = next;
		if (current != NULL)
			current->past = NULL;
	}
}

char	**copy_with_lst(t_env *lst)
{
	int		i;
	char	**copy;

	i = 0;
	copy = malloc(sizeof(char *) * ft_lst_size(lst) + 1);
	if (!copy)
		return (NULL);
	while (lst != NULL)
	{
		copy[i] = ft_strdup(lst->data);
		lst = lst->next;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
