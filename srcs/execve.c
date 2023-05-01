/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 06:59:43 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:36:07 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_args3(char *line)
{
	char	*new;

	new = NULL;
	new = new_line(line);
	free(line);
	return (new);
}

static char	**path_ex(char **env)
{
	char	**bash;
	char	*path;

	path = NULL;
	bash = NULL;
	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	bash = ft_split(path, ':');
	free(path);
	return (bash);
}

static char	**shlvl(t_env *lst, char **env)
{
	char	*level;
	char	*shlvl;
	int		j;

	level = NULL;
	shlvl = NULL;
	level = ft_getenv(env, "SHLVL");
	j = ft_atoi(level);
	j++;
	free(level);
	level = ft_itoa(j);
	Shlvl = ft_sjoin("SHLVL=", level);
	remplace_lst(lst, shlvl);
	free(level);
	free(shlvl);
	free_tt(env);
	env = copy_with_lst(lst);
	return (env);
}

static void	ft_execve2(char **args, t_env *lst, char **env)
{
	int		i;
	char	*gdee;

	i = -1;
	gdee = gde();
	if (ft_strcmp(args[0], "minishell") || ft_strcmp(args[0], "./minishell"))
		env = shlvl(lst, env);
	execve(args[0], args, env);
	printf("%s: ", gdee);
	free(gdee);
	args[0] = convert_args3(args[0]);
	printf("%s", args[0]);
	printf(": command not found\n");
	check_cmd_is_right(127);
	free_tt(args);
}

int	ft_execve(t_cmds *cmd, t_env *lst)
{
	char	**args;
	char	**bash;
	char	*join;
	char	**env;

	env = copy_with_lst(lst);
	args = ft_split(cmd->cmd_args, ' ');
	bash = path_ex(env);
	if (bash && !((args[0][0] == '.' && args[0][1]
		&& args[0][1] == '/') || args[0][0] == '/'))
	{
		while (*bash)
		{
			join = ft_join(*bash++, args[0]);
			execve(join, args, env);
			free(join);
		}
	}
	ft_execve2(args, lst, env);
	free_tt(env);
	exit(127);
	return (0);
}
