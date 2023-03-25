/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:58:09 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/23 16:18:57 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	contain_export(char *ex, char *s)
{
	int i;

	i = 0;
	while (ex[i])
	{
		if (s[i] != ex[i])
			return (0);
		i++;
	}
	return (1);
}

int	get_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_strcmp("echo", cmd))
		return (1);
	else if (ft_strcmp("pwd", cmd))
		return (2);
	else if (ft_strcmp("env", cmd))
		return (4);
	else if (ft_strcmp("unset", cmd))
		return (5);
	else if (ft_strcmp("export", cmd))
		return (6);
	else if (ft_strcmp("cd", cmd))
		return (7);
	else if (contain_export("export", cmd))
		return (6);
	return (0);
}

static void	check_bulltin(t_cmds *cmd, char **env)
{
	if (!cmd->cmd)
		return ;
	//else if (get_cmd(cmd->cmd) == 1)
	//	echo(cmd, env, 1, 0);
	else if (get_cmd(cmd->cmd) == 2)
		pwd();
	else if (get_cmd(cmd->cmd) == 4)
	{
		print_env(env);
		return ;
	}
	/*else if (get_cmd(cmd->cmd) == 5)
	{
		if (cmd->args[1] && env[0])
			unset(cmd, env, 0, 1);
		else
			printf("\n");
		return;
	}
	else if (get_cmd(cmd->cmd) == 6)
	{
		export(cmd, env, 1);
		return;
	}*/
	//else if (get_cmd(cmd->cmd) == 7)
	//	cd(cmd, env);
	else
		ft_execve(cmd, env);
	exit(0);
}

void	check_all_cmd(t_cmds *cmd)
{
	char **args;
	char *str;

	str = env_conversion(cmd->cmd_args, g_ms.env, -1, 0);
	if (!str)
		return;
	args = ft_split(str, ' ');
	if (!args)
		return;
	check_bulltin(cmd, g_ms.env);
	free_tt(args);
	free(str);
}