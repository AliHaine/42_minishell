/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:08:37 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 16:57:17 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// modife faite line 43

static char	*get_curr_w_helper(int q, int i, int *a, char *s)
{
	char	*new;

	new = malloc(sizeof(char) * i + 1);
	*a = *a - i;
	i = 0;
	while (s[*a])
	{
		update(s[*a], &q);
		if (q == 0 && (s[*a] == ' ' || s[*a] == is_redir_char(s[*a])
				|| is_and_or_pipe(s[*a])))
			break ;
		new[i++] = s[*a];
		*a = *a + 1;
	}
	new[i] = '\0';
	new = convert_args3(new);
	return (new);
}

char	*get_current_word(char *s, int *a, int i, int q)
{
	while (s[*a])
	{
		update(s[*a], &q);
		if (q == 0 && (s[*a] == ' ' || s[*a] == is_redir_char(s[*a])
				|| is_and_or_pipe(s[*a])))
			break ;
		i++;
		*a = *a + 1;
	}
	return (get_curr_w_helper(q, i, a, s));
}

char	*ft_strjoin_parse(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*new;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (0);
	new = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new)
		return (0);
	while (s1[a])
	{
		new[a] = s1[a];
		a++;
	}
	new[a++] = ' ';
	while (s2[b])
		new[a++] = s2[b++];
	new[a] = '\0';
	free(s1);
	return (new);
}
