/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:58:09 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/13 16:37:36 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_cmd(char *cmd)
{
	if (ft_strcmp("echo", cmd))
		return (1);
	else if (ft_strcmp("pwd", cmd))
		return (2);
	else if (ft_strcmp("exit", cmd))
		return (3);
	else if (ft_strcmp("env", cmd))
		return (4);
	else if (ft_strcmp("unset", cmd))
		return (5);
	else if (ft_strcmp("export", cmd))
		return (6);
	else if (ft_strcmp("cd", cmd))
		return (7);
	return (0);
}

static void check_bulltin(char **cmd, char **env)
{
	char **str;

	if (!cmd[0])
		return ;
	else if (get_cmd(cmd[0]) == 1)
		echo(cmd, env, 1, 0);
	else if (get_cmd(cmd[0]) == 2)
		pwd();
	else if (get_cmd(cmd[0]) == 3)
		ms.exit = 0;
	else if (get_cmd(cmd[0]) == 4)
		print_env(env);
	else if (get_cmd(cmd[0]) == 5)
	{
		if (cmd[1] && env[0])
			unset(cmd ,env, 0, 1);
		else
			printf("\n");
	}
	else if (get_cmd(cmd[0]) == 6)
		export(cmd, env, 1);
	else if (get_cmd(cmd[0]) == 7)
		cd(cmd, env);
	else
		ft_execve(cmd, env);
	exit(0);
}


// check_all_cmd //

void check_all_cmd(char *line)
{
	char **args;
	char *str;
	int i;

	i = 0;
	str = env_conversion(line, ms.env);\
	if (!str)
		return ;
	args = ft_split(str, ' ');
	if (!args)
	{
		free(line);
		return ;
	}
	check_bulltin(args, ms.env);
	free_tt(args);
	free(line);
	return ;
}