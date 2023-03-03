/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/03 16:28:31 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cd(char **cmd, char **env)
{
	if (cmd[0] && !cmd[1])
	{
		if (chdir(ft_getenv(env, "HOME")) == 0)
			return (0);
		else
			printf("%s: cd: No such file or directory\n", g_d_e());
	}
	else if (cmd[0] && cmd[1][0] == '~')
	{
		chdir(ft_getenv(env, "HOME"));
		if  (cmd[1][1] == '/')
		{
			if (chdir(cmd[1] + 2) == 0)
				return (0);
			else
				printf("cd: no such file or directory: ");
			return (1);
		}
	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (0);
		else
			printf("%s: cd: %s: No such file or directory\n", g_d_e(), cmd[1]);
	}
	return (0);
}