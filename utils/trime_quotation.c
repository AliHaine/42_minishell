/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/09 00:49:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int update(char c, int *in_q)
{
    if (c == '\'' && *in_q != 2)
    {
        *in_q = 1 - (1 * (*in_q == 1));
        return (1);   
    }
    if (c == '\"' && *in_q != 1)
    {
        *in_q = 2 - (2 * (*in_q == 2));
        return (1);
    }
}

int Check_cmd_is_right(int fd)
{
    if (fd == 1)
    {
        
        return (1);
    }
    else
    {
        perror(stderr(errno));
        return (-1);
    }
    return (0);
}