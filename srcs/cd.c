/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/04 14:50:05 by mbouaza          ###   ########.fr       */
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
	return (check_cmd_is_right(1));
}

static int	cd_extend2(char **arg)
{
	char	*gde;

	gde = g_d_e();
	printf("%s: cd: %s: No such file or directory\n", gde, arg[0]);
	free(gde);
	return (check_cmd_is_right(1));
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
		printf("%s: cd: OLDPWD not set\n", old);
	else
		printf("%s\n", get);
	free(old);
	free(get);
	free(gwd);
	remplace_env(env, pwd_path);
	free(pwd_path);
	return (check_cmd_is_right(0));
}

static int	cd_extend4(int choice, char **cmd, char **env)
{
	char	*get;
	char	*gde;

	get = ft_getenv(env, "OLDPWD");
	gde = g_d_e();
	if (choice == 1)
	{
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

// 25 line //

int	cd(char *cmd, char **arg, char **env, t_env *list)
{
	char	*gpwd;
	char	*getenv;
	char	**get;

	get = malloc(sizeof(char *) * 1);
	gpwd = g_pwd();
	get[0] = ft_sjoin("OLDPWD=", gpwd);
	get[1] = NULL;
	getenv = NULL;
	if (cmd && arg[0] && arg[0][0] == '-' && !arg[0][1])
		return (free_tt(get), free(gpwd), cd_extend4(0, arg, env));
	export(get, list, 0);
	free_tt(get);
	if (cmd && (!arg[0] || (arg[0][0] == '~' && !arg[0][1])))
	{
		getenv = ft_getenv(env, "HOME");
		if (getenv && chdir(getenv) != 0)
			return (free(gpwd), cd_extend4(1, arg, env));
		if (getenv)
			free(getenv);
	}
	else if (cmd && arg[0][0] == '~' && arg[0][1] == '/')
	{
		getenv = ft_getenv(env, "HOME");
		if (getenv && chdir(getenv))
			return (free(gpwd), free(getenv), cd_extend(arg));
		if (getenv)
			free(getenv);
	}
	else
		if (chdir(arg[0]) != 0)
			cd_extend2(arg);
	g_ms.old = 1;
	remplace_env(env, ft_sjoin("PWD=", gpwd));
	free(gpwd);
	return (check_cmd_is_right(0));
}
