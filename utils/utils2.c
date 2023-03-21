/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:47:01 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 07:44:32 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// change path //

static char	*change_path(char *argv)
{
	int		i;
	char	*new_argv;

	i = ft_strlen(argv);
	new_argv = malloc(sizeof(char) * i + 2);
	if (!new_argv)
		return (NULL);
	i = 0;
	while (argv[i] && simp_char(argv[i], " \t\n\r\v") == 0)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[i++] = '=';
	new_argv[i] = '\0';
	free(argv);
	return (new_argv);
}

// check path //

int	check_path(char *argv, char **env, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (n == 1)
		argv = change_path(argv);
	if (!argv)
		return (0);
	while (env[j])
	{
		i = 0;
		while (argv[i] == env[j][i])
		{
			if (env[j][i] == '=' && argv[i] == '=')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	char_cmp(char *str, char *reject)
{
	int	i;
	int	j;

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
