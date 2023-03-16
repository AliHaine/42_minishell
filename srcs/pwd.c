/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:47:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/13 17:02:33 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* pwd */

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	check_cmd_is_right(0);
}

/* get the end of the path */

char	*g_d_e(void)
{
	char	*path;
	char	*doc;
	int		i;
	int		x;

	i = 0;
	x = 0;
	path = getcwd(NULL, 0);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	doc = malloc(sizeof(char) * (ft_strlen(path) - i) + 4);
	while (path[i])
		doc[x++] = path[i++];
	doc[x++] = '$';
	doc[x++] = ' ';
	doc[x] = '\0';
	free(path);
	return (doc);
}
