/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:41:12 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// var //

int	var_c(char *s, int i)
{
	int		in_q;
	int		in_dq;
	int		in_sq;
	int		j;

	in_dq = 0;
	in_sq = 0;
	j = 0;
	while (j < i)
		update_sd(s[j++], &in_q, &in_sq, &in_dq);
	if (in_sq % 2 != 0)
		return (1);
	return (0);
}
