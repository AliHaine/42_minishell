/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:37:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/22 14:04:47 by mbouaza          ###   ########.fr       */
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

/*static int check_if_exist(char *path, char **env, int i)
{
	
}*/

/* en cour ... */

static void add_env_var(char **env, char **path)
{
	int i;

	i = 0;
	(void)path;
	while (env[i])
		i++;
	printf("%s\n", env[i - 2]);
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
			{
				free(env[i]);
				env[i] = ft_strdup(path);
			}
		}
		i++;
	}
	return (0);
}

/* juste export seul marche */

void export(char **argv, char **env)
{
	if (!argv[1])
		export_and_nothing(env);
	/*else if (argv[1])
	{
		add_env_var(env, &argv[1]);
	}*/
}