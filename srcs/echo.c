/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:18:28 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/26 20:59:03 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// guillemet // 

/* var type $PATH and var '"$PATH"' 'PATH' */


static int check_is(char *str, char **env, int j, char *reject)
{
	int i;
	int x;
	char *path;

	i = j + 1;
	x = 0;
	path = NULL;
	while (str[i - 1] && path == NULL)
	{
		x = 0;
		while (reject[x])
		{
			if (str[i] == reject[x] || str[i] == '\0')
			{
				path = ft_substr(str, j, i);
				printf("%s", getenv(path + 1));
				return (i - 1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

static int get_env_var(char **env, char *var)
{
	int len;
	int i;
	int j;

	j = 0;
	len = 0;
	i = 0;
	while (var[j] != '=' && var[j])
		j++;
	while (env[i])
	{
		len = 0;
		while (var[len])
		{
			if (env[i][len] && env[i][len] == var[len])
				len++; 
			else
				break;
			if (env[i][len] && env[i][len] == '=' && len < j)
				return (1);
		}
		i++;
	}
	return (0);
}

/* bulltin echo part 2 */

static int echo_2(char **tab, int bulltin)
{
	int i;
	int x;

	i = bulltin + 1;
	x = 2;
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		while (tab[i][x])
		{
			if (tab[i][x] == 'n')
				x++;
			else
			{
				return (bulltin);
			}
		}
		return (echo_2(tab, bulltin + 1));
	}
	return (bulltin);
}

// bulltin echo //

void echo(char **tab, char **env)
{
	int i;
	int j;
	int bulltin;

	i = 1;
	j = 0;
	bulltin = 0;
	if(tab[i])
	{
		i = 1;
		bulltin = echo_2(tab, bulltin);
		if (bulltin > 0)
			i += bulltin;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j] )
			{
				if (tab[i][j] == '$')
				{
					j += check_is(tab[i], env, j, "\t\n\r@&()[]{}%!<>?-*+^~ ;\\|$");
					j++;
				}
				else
					printf("%c", tab[i][j++]);
			}
			i++;
			if (tab[i])
				printf(" ");
		}
	}
	if (bulltin == 0)
		printf("\n");
}