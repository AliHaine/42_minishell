/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:40:21 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/03 18:11:32 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	unset_extend(char **p, int x)
{
	char	*gde;

	gde = g_d_e();
	printf("%s: unset: %s: not a valid identifier\n", gde, p[x]);
	free(gde);
	check_cmd_is_right(1);
	return (0);
}

static int	check_char(char *s, char *reject)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (reject[j] == s[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// $#=+-/@.^%!-?.,;:{}[]&

static void	delete_path(t_env **lst)
{
	t_env	*prevent;
	t_env	*test;

	prevent = (*lst)->past;
	test = (*lst)->next;
	free((*lst)->data);
	free(*lst);
	prevent->next = test;
	test->past = prevent;
	*lst = prevent;
}

// fonction qui enleve et remonte tous d'un noeud

int	unset(char **path, t_env *list, int x)
{
	int	len;

	while (list->next != NULL)
	{
		len = 0;
		while (path[x][len])
		{
			if (check_char(path[x], "$#=+-/@.^%!-?.,;:{}[]&") == 1)
				return (unset_extend(path, x));
			if (list->data[len] && list->data[len] == path[x][len])
				len++;
			else
				break ;
			if (!path[x][len] && list->data[len] == '=')
			{
				delete_path(&list);
				ft_lst_back(&list);
			}
		}
		list = list->next;
	}
	ft_lst_back(&list);
	if (path[x + 1])
		unset(path, list, x + 1);
	return (check_cmd_is_right(0));
}
