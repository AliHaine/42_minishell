/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/21 15:50:22 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(char *const *args, char **env)
{
	char	**bash;
	int		in_q;
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
	i = -1;
	printf("%s: ", gde());
	while (args[0][++i])
		if (!update(args[0][i], &in_q))
			printf("%c", args[0][i]);
	printf(": command not found\n");
	check_cmd_is_right(127);
	return (0);
}
