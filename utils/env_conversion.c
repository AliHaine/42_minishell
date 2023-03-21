/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:01:26 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 08:05:19 by mbouaza          ###   ########.fr       */
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
		return (1);
	return (0);
}

char	*remplace_part(char *s, char *remplace, int start, int end)
{
	int		i;
	int		j;
	int		x;
	char	*new_str;

	i = ft_strlen(remplace);
	x = 0;
	j = 0;
	new_str = NULL;
	new_str = malloc(sizeof(char) * (ft_strlen(s) - (end - start)) + i + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < start)
	{
		new_str[i] = s[i];
		i++;
	}
	j = i + end + 1;
	while (i < start + ft_strlen(remplace))
		new_str[i++] = remplace[x++];
	while (s[j])
		new_str[i++] = s[j++];
	new_str[i] = '\0';
	return (new_str);
}

// a normer //
/* compter le nbr de quote avant et voir si il differe pour le 2eme nbr */

char	*env_conversion(char *s, char **env)
{
	int		i;
	int		j;
	int		q;
	char	*var;

	i = -1;
	j = 0;
	var = NULL;
	while (s[++i])
	{
		if (s[i] == '$' && check_env(s, env, i) == 0 && s[i + 1] != '?')
			while (s[i + 1] && (s[i + 1] >= 'a' && s[i + 1] <= 'z')
				|| (s[i + 1] >= 'A' && s[i + 1] <= 'Z')
				|| (s[i + 1] >= '0' && s[i + 1] <= '9'))
				i++;
		else if (s[i] == '$' && (check_env(s, env, i) == 1
				|| s[i + 1] == '?') && var_c(s, i) == 0)
		{
			j = 0;
			while (s[j + i + 1] && simp_char(s[j + i + 1], " $\'=\"") == 0)
				j++;
			var = ft_substr(s, i + 1, j);
			if (s[i + 1] == '?')
				s = remplace_part(s, ft_itoa(g_ms.stat), i, j);
			else
				s = remplace_part(s, ft_getenv(env, var), i, j);
			i = -1;
		}
	}
	return (s);
}
