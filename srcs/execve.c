/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:25:19 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/13 16:53:34 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve(char *const *args, char **env)
{
	char	**bash;
	pid_t	pid;
	int		i;
	int		test;

	pid = fork();
	i = 0;
	test = -1;
	if (pid == 0)
	{
		bash = ft_split(ft_getenv(env, "PATH"), ':');
		if (!bash)
			return (-1);
		while (bash[i])
			test = execve(ft_join(bash[i++], args[0]), args, NULL);
		perror(strerror(errno));
		return (Check_cmd_is_right(127));
	}
	else
		waitpid(pid, &test, 0);
	return (Check_cmd_is_right(0));
}
