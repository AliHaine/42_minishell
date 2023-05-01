/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:50:07 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:38:52 by mbouaza          ###   ########.fr       */
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
	int		size;
	char	**copy;

	i = 0;
	size = ft_lst_size(lst);
	copy = malloc(sizeof(char *) * (size + 1));
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

int	asciicmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s2[i] > s1[i])
			return (1);
		else if (s2[i] < s1[i])
			return (0);
		i++;
	}
	return (0);
}

int	update_sd(char c, int *in_q, int *qs, int *qd)
{
	if (c == '\'' && *in_q != 2)
	{
		*in_q = 1 - (1 * (*in_q == 1));
		*qs += 1;
		return (1);
	}
	if (c == '\"' && *in_q != 1)
	{
		*in_q = 2 - (2 * (*in_q == 2));
		*qd += 1;
		return (1);
	}
	return (0);
}

int	check_quote(char *s)
{
	int	in_q;
	int	count_s;
	int	count_d;
	int	i;

	i = -1;
	count_d = 0;
	count_s = 0;
	while (s[++i])
		update_sd(s[i], &in_q, &count_s, &count_d);
	if (count_d % 2 != 0 || count_s % 2 != 0)
	{
		printf("quote error\n");
		return (1);
	}
	return (0);
}
