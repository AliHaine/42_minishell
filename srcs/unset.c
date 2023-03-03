/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:40:21 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/03 10:29:29 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_char(char *s, char *reject)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while(reject[j])
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

static int delete_path(char **env, int i)
{
	char *tmp;

	if (env[i + 1])
	{
		tmp = ft_strdup(env[i + 1]);
		if (!tmp)
			return (0);
		env[i] = tmp;
	}
	if (!env[i + 1])
	{
		env[i] = NULL;
		return (0);
	}
	return (delete_path(env, i + 1));
}

int unset(char **path, char **env, int i, int x)
{
	int len;

	len = 0;
	while (env[i])
	{
		len = 0;
		while (path[x][len])
		{
			if (check_char(path[x], "$#=+-/@.^%!-?.,;:{}[]&") == 1)
			{
				printf("%s: unset: %s: not a valid identifier\n", g_d_e(), path[x]);
				return (0);
			}
			if (env[i][len] && env[i][len] == path[x][len] )
				len++; 
			else
				break;
			if (!path[x][len] && env[i][len] == '=')
				delete_path(env, i);
		}
		i++;
	}
	if (path[x + 1])
		unset(path, env, 0, x + 1);
	return (0);
}