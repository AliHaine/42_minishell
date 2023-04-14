/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:47:01 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/07 15:52:54 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (new_argv);
}

// check path //

int	check_path(char *argv, char **env, int n)
{
	int			i;
	int			j;
	char		*copy;

	j = 0;
	if (n == 1)
		copy = change_path(argv);
	else
		copy = ft_strdup(argv);
	if (!copy)
		return (0);
	while (env[j])
	{
		i = 0;
		while (copy[i] == env[j][i])
		{
			if (env[j][i] == '=' && copy[i] == '=')
				return (free(copy), 1);
			i++;
		}
		j++;
	}
	return (free(copy), 0);
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

int	check_path_lst(char *argv, t_env *lst, int n)
{
	int		i;
	char	*copy;

	i = 0;
	if (n == 1)
		copy = change_path(argv);
	else
		copy = ft_strdup(argv);
	if (!copy)
		return (0);
	while (lst != NULL)
	{
		i = 0;
		while (copy[i] == lst->data[i])
		{
			if (lst->data[i] == '=' && copy[i] == '=')
				return (free(copy), 1);
			i++;
		}
		lst = lst->next;
	}
	return (free(copy), 0);
}

int	char_ccmp(char c, char *reject)
{
	int	j;

	j = 0;
	while (reject[j])
	{
		if (c == reject[j])
			return (1);
		j++;
	}
	return (0);
}
