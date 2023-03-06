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

// copy temporaire

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	return (dst);
}