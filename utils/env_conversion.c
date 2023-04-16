/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:01:26 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/16 19:13:13 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simp_char(char c, char *reject)
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

static int	check_env(char *s, char **env, int i)
{
	int		j;
	char	*path;

	j = i;
	path = NULL;
	while (s[j] && simp_char(s[j + 1], " $\'=\"") == 0)
				j++;
	path = ft_substr(s, i + 1, j - i);
	if (!path)
		return (0);
	if (check_path(path, env, 1) == 1)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

void	rat(char *var, char *itoa, char *genv)
{
	free(var);
	free(itoa);
	free(genv);
}

static int	ft_while(char *s, int i)
{
	int j;

	j = 0;
	while (char_ccmp(s[i], " $\"\'="))
	{
		i++;
		j++;
	}
	return (j);
}

char	*env_conversion(char *s, char **env, int i, int j)
{
	char	*var;
	char	*genv;
	char	*itoa;

	while (s[++i])
	{
		if (s[i] == '$' && check_env(s, env, i) == 0 && s[i + 1] != '?')
			s = remplace_part(s, " ", i, ft_while(s, i));
		else if (s[i] == '$' && (check_env(s, env, i) == 1
				|| s[i + 1] == '?') && var_c(s, i) == 0)
		{
			while (s[j + i + 1] && simp_char(s[j + i + 1], " $\'=\"") == 0)
				j++;
			var = ft_substr(s, i + 1, j);
			genv = ft_getenv(env, var);
			itoa = ft_itoa(g_ms.stat);
			if (s[i + 1] == '?')
				s = remplace_part(s, itoa, i, j);
			else
				s = remplace_part(s, genv, i, j);
			i = -1;
			rat(var, genv, itoa);
		}
	}
	return (s);
}
