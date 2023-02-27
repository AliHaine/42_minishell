/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:14:14 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/24 17:42:58 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 

➜  ~ cd ~/Downloads
➜  Downloads pwd
/Users/mbouaza/Downloads
➜  Downloads cd -
~
➜  ~ cd -
~/Downloads
➜  Downloads cd -
~
➜  ~

*/

//  chemin rapide : en cour //

int cd(char **cmd, char **env)
{
	if (cmd[0] && !cmd[1])
	{
		if (chdir(getenv("HOME")) == 0)
			return (0);
		else
			printf("%s: cd: No such file or directory\n", g_d_e());
	}
	else if (cmd[0] && cmd[1][0] == '~')
	{
		if (chdir(getenv("HOME")) == 0)
		{
			if (chdir(getenv(cmd[1] + 1)) == 0)
				printf("%s\n", cmd[1] + 1);
		}
		else
		{
			printf("cd: no such file or directory: ");
			printf("%s", getenv("HOME"));
		}

	}
	else
	{
		if (chdir(cmd[1]) == 0)
			return (0);
		else
			printf("%s: cd: %s: No such file or directory\n", g_d_e(), cmd[1]);
	}
	return (0);
}