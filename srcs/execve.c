/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/13 19:31:33 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_args3(char *line)
{
	char	*new;

	new = new_line(line);
	free(line);
	return (new);
}

static char	**path_ex(char **env)
{
	char	**bash;
	char	*path;

	path = ft_getenv(env, "PATH");
	bash = ft_split(path, ':');
	free(path);
	return (bash);
}

static void	ft_execve2(char **args, char **env)
{
	int		i;
	char	*gdee;

	i = -1;
	gdee = gde();
	execve(args[0], args, env);
	printf("%s: ", gdee);
	free(gdee);
	printf("%s", args[0]);
	printf(": command not found\n");
	check_cmd_is_right(127);
	free_tt(args);
}

static void	not_found(char *cmd)
{
	char	*gdee;

	gdee = gde();
	printf("%s: ", gdee);
	free(gdee);
	printf("%s", cmd);
	printf(": command not found\n");
	exit(127);
}

int	ft_execve(t_cmds *cmd, t_env *lst)
{
	char	**args;
	char	**bash;
	char	*join;
	char	**env;

	env = copy_with_lst(lst);
	args = ft_split(cmd->cmd_args, ' ');
	if (check_path_lst("PATH=", lst, 0) == 0)
		not_found(args[0]);
	bash = path_ex(env);
	while (*bash)
	{
		join = ft_join(*bash++, args[0]);
		execve(join, args, env);
		free(join);
	}
	ft_execve2(args, env);
	free_tt(env);
	exit(127);
	return (0);
}
