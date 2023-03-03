/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/03/03 15:25:26 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void convert_quotes(char *str) 
{
    int len;
    int starts_with_quote;
    int ends_with_quote;

    len = strlen(str);
    starts_with_quote = (len > 0 && (str[0] == '"' || str[0] == '\''));
    ends_with_quote = (len > 0 && (str[len-1] == '"' || str[len-1] == '\''));
    if (!starts_with_quote && !ends_with_quote) 
    {
        
    }
    else if (starts_with_quote && ends_with_quote && str[0] == str[len-1]) 
    {
        ft_memmove(str, str+1, len-2);
        str[len-2] = '\0';
    }
    else if (starts_with_quote && ends_with_quote && str[0] != str[len-1]) 
    {
    }
    else if (starts_with_quote) 
    {
        ft_memmove(str, str+1, len-1);
        str[len-1] = '\0';
    }
    else if (ends_with_quote) 
        str[len-2] = '\0';
}