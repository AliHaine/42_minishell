/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:58:09 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/04 03:57:54 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	contain_export(char *ex, char *s)
{
	int	i;

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

static void	check_builtin_h(t_cmds *cmd, t_env *list, char **env)
{
	if (get_cmd(cmd->cmd) == 5)
	{
		if (g_ms.cmds_f->args[0] && list->data)
			unset(g_ms.cmds_f->args, list, 0);
		return ;
	}
	else if (get_cmd(cmd->cmd) == 6)
	{
		export(g_ms.cmds_f->args, list, 0);
		if (g_ms.cmd_nbr == 1)
			return ;
	}
	else if (get_cmd(cmd->cmd) == 7)
	{
		env = copy_with_lst(list);
		cd(g_ms.cmds_f->cmd, g_ms.cmds_f->args, g_ms.env, list);
		free_tt(env);
		if (g_ms.cmd_nbr == 1)
			return ;
	}
}

static void	check_bulltin(t_cmds *cmd, t_env *list)
{
	if (!cmd->cmd)
		return ;
	else if (get_cmd(cmd->cmd) == 1)
		echo(cmd->args, 0, 0);
	else if (get_cmd(cmd->cmd) == 2)
		pwd();
	else if (get_cmd(cmd->cmd) == 4)
	{
		print_env(cmd, list);
		if (g_ms.cmd_nbr == 1)
			return ;
	}
	else if (get_cmd(cmd->cmd) == 5 || get_cmd(cmd->cmd) == 6
		|| get_cmd(cmd->cmd) == 7)
		return (check_builtin_h(cmd, list, 0));
	else
		ft_execve(cmd);
	exit(0);
}

void	check_all_cmd(t_cmds *cmd, t_env *list)
{
	check_bulltin(cmd, list);
}
