/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:46:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/28 16:25:53 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// str_copy //

int	str_copy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (size > 0)
	{
		dst[i] = src[i];
		size--;
		i++;
	}
	dst[i] = '\0';
	return (i);
}

// copy env //

char	**copy_env(char **env, int size)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * size + 1);
	if (!copy)
		return (NULL);
	while (i < size)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// sort env //

// leak regles //

char	**print_sorted_strings(char **env, int size)
{
	int		i;
	int		j;
	char	*temp;
	char	**strings;

	i = 0;
	j = 0;
	temp = NULL;
	strings = copy_env(env, size);
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (strcmp(strings[j], strings[j + 1]) > 0)
			{
				temp = ft_strdup(strings[j]);
				free(strings[j]);
				strings[j] = ft_strdup(strings[j + 1]);
				free(strings[j + 1]);
				strings[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	return (strings);
}

// ft_join //

char	*ft_join(char *s1, char *s2)
{
	int		len;
	int		len2;
	char	*newstr;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	len2 = 0;
	newstr = (char *)malloc(sizeof(char) * (len + 2));
	if (!newstr)
		return (0);
	len = 0;
	while (s1[len2])
		newstr[len++] = s1[len2++];
	newstr[len++] = '/';
	len2 = 0;
	while (s2[len2])
		newstr[len++] = s2[len2++];
	newstr[len] = '\0';
	return (newstr);
}

// ft_sjoin //

char	*ft_sjoin(char *s1, char *s2)
{
	int		len;
	int		len2;
	char	*newstr;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	len2 = 0;
	newstr = (char *)malloc(sizeof(char) * (len + 2));
	if (!newstr)
		return (0);
	len = 0;
	while (s1[len2])
		newstr[len++] = s1[len2++];
	len2 = 0;
	while (s2[len2])
		newstr[len++] = s2[len2++];
	newstr[len] = '\0';
	return (newstr);
}
