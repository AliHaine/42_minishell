/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/10 16:18:11 by mbouaza          ###   ########.fr       */
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
    return (0);
}

int Check_cmd_is_right(int fd)
{
    if (fd == 1)
    {
        
        return (1);
    }
    else
    {
        return (-1);
    }
    return (0);
}