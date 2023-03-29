/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/29 13:32:28 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// en fonction de ou se trouve cd le nbr (taille du nom du fichier) de leak augmente

static int	cd_extend(char **arg)
{
	if (chdir(arg[0] + 2) != 0)
		return (check_cmd_is_right(0));
	printf("cd: %s: No such file or directory: ", arg[0]);
	return (check_cmd_is_right(1));
}

static int	cd_extend2(char **arg)
{
	printf("%s: cd: %s: No such file or directory\n", g_d_e(), arg[0]);
	return (check_cmd_is_right(1));
}

static int	cd_extend3(char **env)
{
	printf("%s\n", ft_getenv(env, "OLDPWD"));
	remplace_env(env, ft_sjoin("PWD=", g_pwd()));
	return (check_cmd_is_right(0));
}

static int	cd_extend4(int choice, char **cmd, char **env)
{
	if (choice == 1)
	{
		printf("cd: %s: No such file or directory:\n", g_d_e());
		return (check_cmd_is_right(1));
	}
	else
	{
		if (chdir(ft_getenv(env, "OLDPWD")) != 0)
			return (cd_extend2(cmd));
		return (cd_extend3(env));
	}
	return (0);
}	

// 25 line //

int	cd(char *cmd, char **arg, char **env)
{
	char	*gpwd;
	char	*getenv;

	gpwd = g_pwd();
	if (cmd && arg[0] && arg[0][0] == '-' && !arg[0][1])
		return (cd_extend4(0, arg, env));
	remplace_env(env, ft_sjoin("OLDPWD=", gpwd));
	if (cmd && (!arg[0] || (arg[0][0] == '~' && !arg[0][1])))
	{
		getenv = ft_getenv(env, "HOME");
		if (getenv && chdir(getenv) != 0)
			return (cd_extend4(1, arg, env));
		if (getenv)
			free(getenv);
	}
	else if (cmd && arg[0][0] == '~' && arg[0][1] == '/')
	{
		getenv = ft_getenv(env, "HOME");
		if (getenv && chdir(getenv))
			return (cd_extend(arg));
		if (getenv)
			free(getenv);
	}
	else
		if (chdir(arg[0]) != 0)
			cd_extend2(arg);
	remplace_env(env, ft_sjoin("PWD=", gpwd));
	free(gpwd);
	return (check_cmd_is_right(0));
}
