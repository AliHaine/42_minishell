/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/13 00:28:30 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// en fonction de ou se trouve cd
// le nbr (taille du nom du fichier) de leak augmente

static int	cd_extend(char **arg)
{
	if (chdir(arg[0] + 2) != 0)
		return (check_cmd_is_right(0));
	printf("cd: %s: No such file or directory: ", arg[0]);
	g_ms.stat = 1;
	return (1);
}

static int	cd_extend2(char **arg)
{
	char	*gde;

	gde = g_d_e();
	printf("%s: cd: %s: No such file or directory\n", gde, arg[0]);
	free(gde);
	g_ms.stat = 1;
	return (1);
}

static int	cd_extend3(char **env)
{
	char	*get;
	char	*pwd_path;
	char	*gwd;
	char	*old;

	old = g_d_e();
	get = ft_getenv(env, "OLDPWD");
	gwd = g_pwd();
	pwd_path = ft_sjoin("PWD=", gwd);
	if (g_ms.old < 1)
	{
		g_ms.stat = 1;
		printf("%s: cd: OLDPWD not set\n", old);
	}
	else
		printf("%s\n", get);
	free(old);
	free(get);
	free(gwd);
	remplace_env(env, pwd_path);
	free(pwd_path);
	return (0);
}

static int	cd_extend4(int choice, char **cmd, char **env)
{
	char	*get;
	char	*gde;

	get = ft_getenv(env, "OLDPWD");
	gde = g_d_e();
	if (choice == 1)
	{
		g_ms.stat = 1;
		printf("cd: %s: No such file or directory:\n", gde);
		return (free(get), free(gde), check_cmd_is_right(1));
	}
	else
	{
		if (chdir(get) != 0)
			return (free(get), free(gde), cd_extend2(cmd));
		return (free(get), free(gde), cd_extend3(env));
	}
	return (0);
}

// fonction qui free en fonction du nbr de i //

int	cd(char *cmd, char **arg, char **env)
{
	char	**get;

	get = get_null(3);
	get[0] = grattage();
	if (cmd && arg[0] && arg[0][0] == '-' && !arg[0][1])
		return (get_free(get, 1), cd_extend4(0, arg, env));
	get[1] = g_pwd();
	get[2] = ft_getenv(env, "HOME");
	if (cmd && (!arg[0] || (arg[0][0] == '~' && !arg[0][1])))
	{
		if (get[2] && chdir(get[2]) != 0)
			return (get_free(get, 3), cd_extend4(1, arg, env));
	}
	else if (cmd && arg[0][0] == '~' && arg[0][1] == '/')
	{
		if (get[2] && chdir(get[2]))
			return (get_free(get, 3), cd_extend(arg));
	}
	else
		if (chdir(arg[0]) != 0)
			cd_extend2(arg);
	g_ms.old = 1;
	remplace_env(env, get[0]);
	return (get_free(get, 3), 0);
}
