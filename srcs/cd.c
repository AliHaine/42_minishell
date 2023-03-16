/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/13 17:03:55 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_extend(char **cmd)
{
	if (chdir(cmd[1] + 2) == 0)
		return (check_cmd_is_right(1));
	else
		printf("cd: no such file or directory: ");
	return (check_cmd_is_right(0));
}	

int	cd(char **cmd, char **env)
{
	if (cmd[0] && !cmd[1])
	{
		if (chdir(ft_getenv(env, "HOME")) == 0)
			return (check_cmd_is_right(1));
		else
			printf("%s: cd: No such file or directory\n", g_d_e());
		return (check_cmd_is_right(1));
	}
	else if (cmd[0] && cmd[1][0] == '~')
	{
		chdir(ft_getenv(env, "HOME"));
		if (cmd[1][1] == '/')
			return (cd_extend(cmd));
		return (check_cmd_is_right(0));
	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (check_cmd_is_right(0));
		else
			printf("%s: cd: %s: No such file or directory\n", g_d_e(), cmd[1]);
	}
	return (check_cmd_is_right(1));
}
