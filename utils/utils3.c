/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:46:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/04 17:21:20 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remplace_part(char *s, char *remplace, int start, int end)
{
	int		i;
	int		j;
	int		x;
	char	*new_str;

	i = ft_strlen(remplace);
	x = 0;
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
	while (i < start + (int) ft_strlen(remplace))
		new_str[i++] = remplace[x++];
	while (s[j])
		new_str[i++] = s[j++];
	new_str[i] = '\0';
	free(s);
	return (new_str);
}

// sort env //

char	**print_sorted_strings(t_env *list, int i, int j)
{
	char	*temp;
	char	**strings;
	int		size;

	size = ft_lst_size(list);
	temp = NULL;
	strings = copy_with_lst(list);
	while (i < size - 1)
	{
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
