/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 07:46:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/03 16:48:56 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	single_fork(t_cmds *cmd, t_t_i ti, t_env *list)
{
	int	r;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (cmd->w == 0)
			check_all_cmd(cmd, list);
		else
			redirection_main(0, cmd, ti, list);
	}
	waitpid(pid, &r, WIFEXITED(pid));
	g_ms.stat = WEXITSTATUS(r);
	return (1);
}

// copy env //

char	**copy_env(t_env *list, int size)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	while (i < size)
	{
		copy[i] = ft_strdup(list->data);
		printf("%s\n", list->data);
		list = list->next;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// sort env //

// leak regles //

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
