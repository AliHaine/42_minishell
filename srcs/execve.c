/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 07:24:15 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(char *const *args, char **env)
{
	char	**bash;
	int		i;

	i = 0;
	bash = ft_split(ft_getenv(env, "PATH"), ':');
	if (!bash)
		return (-1);
	check_cmd_is_right(0);
	while (bash[i])
	{
		execve(ft_join(bash[i++], args[0]), args, NULL);
	}
	printf("%s: %s: command not found\n", gde(), args[0]);
	check_cmd_is_right(127);
	return (0);
}
