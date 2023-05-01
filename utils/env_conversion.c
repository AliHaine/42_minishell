/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:01:26 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:28:00 by mbouaza          ###   ########.fr       */
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

void	rat(char *var, char *genv, int *i)
{
	free(var);
	free(genv);
	*i = -1;
}

static int	ft_while(char *s, int i)
{
	int	j;

	j = 0;
	if (s[i + j] == '$')
		j++;
	while (s[i + j] && char_ccmp(s[i + j], " =$\"\'") == 0)
		j++;
	if (j > 0)
		j--;
	return (j);
}

char	*env_conversion(char *s, char **env, int i, int j)
{
	char	*var;
	char	*genv;

	while (s[++i])
	{
		if (s[i] == '$' && check_env(s, env, i) == 0 && s[i + 1] != '?'
			&& var_c(s, i) == 0)
			s = remplace_part(s, " ", i, ft_while(s, i));
		else if (s[i] == '$' && (check_env(s, env, i) == 1
				|| s[i + 1] == '?') && var_c(s, i) == 0)
		{
			while (s[j + i + 1] && simp_char(s[j + i + 1], " $\'=\"") == 0)
				j++;
			var = ft_substr(s, i + 1, j);
			if (s[i + 1] == '?')
				genv = ft_itoa(g_ms.stat);
			else
				genv = ft_getenv(env, var);
			s = remplace_part(s, genv, i, j);
			rat(var, genv, &i);
		}
	}
	return (s);
}
