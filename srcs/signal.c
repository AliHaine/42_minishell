/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:13:44 by ayagmur           #+#    #+#             */
/*   Updated: 2023/04/13 01:10:52 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(void)
{
	if (g_ms.on_cmd == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_ms.stat = 1;
}

void	ctrl_bs(void)
{
}

void	signal_main()
{
	signal(2, (void *)ctrl_c);
	signal(SIGQUIT, (void *)ctrl_bs);
	rl_catch_signals = 0;
}