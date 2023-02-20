/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:48:58 by mbouaza           #+#    #+#             */
/*   Updated: 2022/11/24 12:49:58 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Get_next_line tools */

/* ft_strlen */

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/* check_new_line : Look for a newline character */

int	check_newline(char c, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/************* ft_strjoin() *************/

/* juste for free() */

static char	*free_all(char *s1)
{
	free(s1);
	return (NULL);
}

/* To gain line (norminette) */

char	*no_pain_no_gain(char *s1, char *s2, char *storage, int i)
{
	int	j;

	j = 0;
	while (s1[j])
		storage[i++] = s1[j++];
	j = 0;
	while (s2[j])
		storage[i++] = s2[j++];
	storage[i] = '\0';
	return (storage);
}

/* ft_strjoin (edited for get_next_line) */

char	*ft_strjoin(char *s1, char *s2)
{
	char	*storage;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (free_all(s1));
		s1[0] = '\0';
	}
	if (s2 == NULL || s1 == NULL)
		return (free_all(s1));
	storage = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (storage == NULL)
		return (free_all(s1));
	storage = no_pain_no_gain(s1, s2, storage, i);
	free(s1);
	return (storage);
}
