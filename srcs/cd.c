/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/19 12:20:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_extend(char **cmd)
{
	if (chdir(cmd[1] + 2) != 0)
		return (check_cmd_is_right(0));
	printf("cd: %s: No such file or directory: ", cmd[1]);
	return (check_cmd_is_right(1));
}

static int	cd_extend2(char **cmd)
{
	 printf("%s: cd: %s: No such file or directory\n", g_d_e(), cmd[1]);
	return (check_cmd_is_right(1));
}	

// 25 line //

int	cd(char **cmd, char **env)
{
	if (cmd[0] && cmd[1] && cmd[1][0] == '-' && !cmd[1][1])
	{
		if (chdir(ft_getenv(env, "OLDPWD")) != 0)
			return (cd_extend2(cmd));
		printf("%s\n", ft_getenv(env, "OLDPWD"));
		remplace_env(env, ft_sjoin("PWD=", g_pwd()));
		return (check_cmd_is_right(0));
	}
	remplace_env(env, ft_sjoin("OLDPWD=", g_pwd()));
	if (cmd[0] && !cmd[1])
	{
		if (chdir(ft_getenv(env, "HOME")) != 0)
		{
			printf("cd: %s: No such file or directory:\n", g_d_e());
			return (check_cmd_is_right(1));
		}
	}
	else if (cmd[0] && cmd[1][0] == '~' && !cmd[1][1])
	{
		if (chdir(ft_getenv(env, "HOME")) != 0)
			return (cd_extend(cmd));
	}
	else if (cmd[0] && cmd[1][0] == '~' && cmd[1][1] == '/')
	{
		if (chdir(ft_getenv(env, cmd[1])) != 0)
			return (cd_extend(cmd));
	}
	else
	{
		if (chdir(cmd[1]) != 0)
			cd_extend2(cmd);
	}
	remplace_env(env, ft_sjoin("PWD=", g_pwd()));
	return (check_cmd_is_right(0));
}
