/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:56:48 by ayagmur           #+#    #+#             */
/*   Updated: 2022/11/20 12:56:49 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *str, int strchar)
{
	int	i;

	i = 0;
	if (((char)strchar) == 0 || !str)
		return (0);
	while (str[i])
	{
		if (str[i] == ((char)(strchar)))
			return (strchar);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

static void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;

	c = malloc(size * count);
	if (c == NULL)
		return (0);
	ft_bzero(c, size * count);
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		x;
	char	*dst;

	i = ft_strlen(((char *)s1)) + ft_strlen(((char *)s2));
	x = 0;
	dst = (char *) malloc(sizeof(char) * (i + 1));
	if (!dst || !s2)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
		x++;
	}
	i = 0;
	while (s2[i])
		dst[x++] = s2[i++];
	dst[x] = '\0';
	free(((char *) s1));
	return (dst);
}
