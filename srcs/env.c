/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:23:35 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/04 17:33:06 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* env env env == env \\ env env eng = error */

void	print_env(t_cmds *cmd, t_env *list)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], "env"))
			i++;
		else
		{
			printf("env: %s: No such file or directory\n", cmd->args[i]);
			check_cmd_is_right(1);
			return ;
		}
	}
	while (list != NULL)
	{	
		printf("%s\n", list->data);
		list = list->next;
	}
	check_cmd_is_right(0);
}

static char	*print_v_env(char **env, int i)
{
	char	*char_env;
	int		j;
	int		len;

	j = 0;
	len = 0;
	char_env = NULL;
	while (env[i][j] != '=')
		j++;
	while (env[i][j])
	{
		len++;
		j++;
	}
	char_env = malloc(sizeof(char) * len + 1);
	if (!char_env)
		return (NULL);
	j = j - (len - 1);
	len = 0;
	while (env[i][j])
		char_env[len++] = env[i][j++];
	char_env[len] = '\0';
	return (char_env);
}

char	*ft_getenv(char **env, char *path)
{
	int		i;
	int		j;
	char	*get;

	i = 0;
	get = NULL;
	while (env[i])
	{	
		j = 0;
		while (env[i][j] == path[j])
		{
			j++;
			if (!path[j] && env[i][j] == '=')
			{
				get = print_v_env(env, i);
				if (!get)
					return (NULL);
				return (get);
			}
		}
		i++;
	}
	return (NULL);
}
