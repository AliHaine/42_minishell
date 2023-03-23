/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:40:21 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/23 16:02:18 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	charcmp(char c, char *reject)
{
	int	i;

	i = 0;
	while (reject[i])
	{
		if (reject[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	unset_extend(char **p, int x)
{
	printf("%s: unset: %s: not a valid identifier\n", g_d_e(), p[x]);
	check_cmd_is_right(1);
	exit(1);
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

static int	delete_path(char **env, int i)
{
	char	*tmp;

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

// si ya \ il faut \\ donc enleve en un //

int	unset(char **path, char **env, int i, int x)
{
	int	len;

	len = 0;
	while (env[i])
	{
		len = 0;
		while (path[x][len])
		{
			if (check_char(path[x], "$#=+-/@.^%!-?.,;:{}[]&") == 1)
				return (unset_extend(path, x));
			if (env[i][len] && env[i][len] == path[x][len])
				len++;
			else
				break ;
			if (!path[x][len] && env[i][len] == '=')
				delete_path(env, i);
		}
		i++;
	}
	if (path[x + 1])
		unset(path, env, 0, x + 1);
	return (check_cmd_is_right(0));
}
