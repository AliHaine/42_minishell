/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:37:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/27 12:07:36 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* probleme de longeur tkt c fini demain */

/* 

export seul = 'declare -x V_ENV="path"' check;
export + V_ENV=W
mettre au dessus du dernier char *

*/

#include "../minishell.h"

static void export_and_nothing(char **env)
{
	int i;
	int j;
	int check;

	check = 0;
	j = 0;
	i = 0;
	while (env[i + 1])
	{
		check = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (env[i][j])
		{
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && check == 0)
			{
				write(1, "\"", 1);
				check = 1;
			}
			j++;
		}
		write(1, "\"", 1);
		printf("\n");
		i++;
	}
}

/* check if export is already exist or not or is valid */

// just do nothing =  ' ' ; \ | $ 

// message = : '\t' '\n' '\r' @ & ( ) [] {} % ! < > ? - * + ^ ~

static int check_valid(char *path)
{
	int check;
	int i;

	check = 0;
	i = 0;
	while (path && path[i] != '=')
	{
		if (char_cmp(path, " ;\\|$") == 1)
			check = 1;
		else if (char_cmp(path, "\t\n\r@&()[]{}%!<>?-*+^~") == 1)
		{
			check = 2;
			break;
		}
		i++;
	}
	if (check == 0)
		return (0);
	else if (check == 2)
		printf("%s: export: '%s': not a valid identifier\n", g_d_e(), path);
	return (1);
}

/* en cour ... */
// leak //

static char **add_env_var(char **env, char *path)
{
	int i;

	i = 0;
	if (env[i])
	{
		i = ft_tablen(env);
		env[i] = ft_strdup(env[i - 1]);
		if (!env[i])
			return (NULL);
		env[i - 1] = ft_strdup(path);
		if (!env[i])
			return (NULL);
		env[i + 1] = NULL;
	}
	return (env);
}

/* pret mais il me faut une fonction de verif */

static char *remplace_env(char **env, char *path)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (env[i])
	{
		len = 0;
		while (path[len])
		{ 
			if (env[i][len] && env[i][len] == path[len])
				len++; 
			else
				break;
			if (path[len] && env[i][len] == '=')
				env[i] = ft_strdup(path);
		}
		i++;
	}
	return (0);
}

/* juste export seul marche */

void export(char **argv, char **env)
{
	char *path;
	int i = 0;

	path = NULL;
	if (!argv[1])
		export_and_nothing(env);
	else if (argv[1])
	{
		if (check_path(argv, env) == 1)
		{
			remplace_env(env, argv[1]);
		}
		else
		{
			if (check_valid(argv[1]) == 0)
				env = add_env_var(env, argv[1]);
		}
	}
}