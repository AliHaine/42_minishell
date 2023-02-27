/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:47:01 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/26 10:04:43 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// check if an env variable exist //

int check_path(char **argv, char **env)
{
	int i;
	int j;


	i = 0;
	while (env[j])
	{
		i = 0;
		while (argv[1][i] == env[j][i])
		{
			if (argv[1][i] == env[j][i] && env[j][i] == '=')
			{
				return (1);
				break;
			}
			i++;
		}
		j++;
	}
	return (0);
}

int char_cmp(char *str, char *reject)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (reject[j])
		{
			if (str[i] == reject[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}