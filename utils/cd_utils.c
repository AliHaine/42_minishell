/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:19:49 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:40:02 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_null(int i)
{
	char	**get;
	int		j;

	j = 0;
	get = malloc(sizeof(char *) * (i + 1));
	while (j < i)
		get[j++] = NULL;
	get[j] = NULL;
	return (get);
}

void	get_free(char **get, int i)
{
	int	j;

	j = 0;
	while (i > j)
		free(get[j++]);
	free(get);
}

char	*grattage(void)
{
	char	*get1;
	char	*get2;

	get2 = g_pwd();
	g_ms.stat = 0;
	get1 = ft_sjoin("OLDPWD=", get2);
	free(get2);
	return (get1);
}
