/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:35:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/16 19:33:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit //

void	exit_shell(void)
{
	struct s_minishell	*ms;

	ms->exit = 0;
}

// For $? //

int check_cmd_is_right(int fd)
{
    if (fd > 0) 
    {
		ms.stat = fd;
        return (-1);
    }
    ms.stat = 0;
    return (0);
}

char *histo_pars(char *histo)
{
    int i;
    char *copy;

    i = ft_strlen(histo) - 1;
     copy = ft_strdup(histo);
    if (!copy)
        return (NULL);
    if (copy[i] && copy[i] == '\n')
        copy[i] = '\0';
    return (copy);
}