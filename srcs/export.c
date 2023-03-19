/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:37:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/19 12:25:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_and_nothing(char **env, int i, int j, int check)
{
	char	**sort_env;

	sort_env = NULL;
	while (env[i])
		i++;
	sort_env = print_sorted_strings(env, i);
	i = 0;
	while (sort_env[i])
	{
		check = 0;
		j = 0;
		write(1, "declare -x ", 11);
		while (sort_env[i][j])
		{
			write(1, &sort_env[i][j], 1);
			if (sort_env[i][j] == '=')
				write(1, "\"", 1);
			j++;
		}
		printf("\"\n");
		i++;
	}
	free(sort_env);
	check_cmd_is_rightell(0);
}

static int	check_valid(char *path)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (path && path[i] != '=')
	{
		if (char_cmp(path, " ;\\|$") == 1)
			check = 1;
		else if (char_cmp(path, "\t\n\r@&()[]{}%!<>?-*+^~") == 1)
		{
			check = 2;
			break ;
		}
		i++;
	}
	if (check == 0)
	{
		check_cmd_is_rightell(0);
		return (0);
	}
	else if (check == 2)
	{
		check_cmd_is_rightell(1);
		printf("%s: export: '%s': not a valid identifier\n", g_d_e(), path);
	}
	return (1);
}

/* en cour ... */
// leak //

static char	**add_env_var(char **env, char *path)
{
	int	i;

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

char	*remplace_env(char **env, char *path)
{
	int	len;
	int	i;

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
				break ;
			if (path[len] && env[i][len] == '=')
			{
				env[i] = ft_strdup(path);
			}
		}
		i++;
	}
	return (0);
}

/* juste export seul marche */

void	export(char **argv, char **env, int i)
{
	char	*path;

	path = NULL;
	if (!argv[i])
	{
		export_and_nothing(env, 0, 0, 0);
		return ;
	}
	else if (argv[i])
	{
		if (check_path(argv[i], env, 0) == 1)
		{
			remplace_env(env, argv[i]);
		}
		else
		{
			if (check_valid(argv[i]) == 0)
				env = add_env_var(env, argv[i]);
		}
	}
	if (argv[i + 1])
		export(argv, env, i + 1);
	check_cmd_is_rightell(0);
}
