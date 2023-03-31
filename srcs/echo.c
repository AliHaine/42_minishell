/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:18:28 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/29 13:23:25 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// guillemet // 

/* var type $PATH and var '"$PATH"' 'PATH' */

/*static int	check_is(char *str, char **env, int j, char *reject)
{
	int		i;
	int		x;
	char	*path;
	char	*get;

	i = j + 1;
	x = 0;
	while (str[i - 1] && path == NULL)
	{
		x = 0;
		while (reject[x])
		{
			if (str[i] == reject[x] || str[i] == '\0')
			{
				path = ft_substr(str, j, i);
				get = ft_getenv(env, path + 1);
				printf("%s", get);
				free(path);
				return (free(get), i - 1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

static int	check_is_true(char *str, char **env, int j, char *reject)
{
	int		i;
	int		x;
	char	*path;

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
				return (1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

static int	get_env_var(char **env, char *var)
{
	int	len;
	int	i;
	int	j;

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
				break ;
			if (env[i][len] && env[i][len] == '=' && len < j)
				return (1);
		}
		i++;
	}
	return (0);
}*/

/* bulltin echo part 2 */

static int	echo_2(char **tab, int bulltin)
{
	int	i;
	int	x;

	i = bulltin;
	x = 2;
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		while (tab[i][x])
		{
			if (tab[i][x] == 'n')
				x++;
			else
				return (bulltin);
		}
		return (echo_2(tab, bulltin + 1));
	}
	return (bulltin);
}

// bulltin echo //

// no leak //

void	echo(char **tab, int i, int j)
{
	int	bulltin;
	int	in_q;

	bulltin = 0;
	in_q = 0;
	if (tab[i])
	{
		bulltin = echo_2(tab, bulltin);
		if (bulltin > 0)
			i += bulltin;
		while (tab[i])
		{
			j = -1;
			while (tab[i][++j])
				if (!update(tab[i][j], &in_q))
					printf("%c", tab[i][j]);
			if (tab[i])
				printf(" ");
			i++;
		}
	}
	if (bulltin == 0)
		printf("\n");
	check_cmd_is_right(0);
}
