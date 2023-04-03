/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:18:28 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/03 16:37:38 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env 		*lst_copy_tab(char **env)
{
	int 	i;
	t_env	*lst;
	char *pwd;
	char *joint;

	pwd = getcwd(NULL, 0);
	joint = ft_sjoin("OLDPWD=", pwd);
	free(pwd);
	i = -1;
	lst = NULL;
	ft_lstadd_back(&lst, joint);
	while (env[++i])
		ft_lstadd_back(&lst, env[i]);
	free(joint);
	return (lst);
}

t_env 		*lst_copy(t_env *lst)
{
	int 	i;
	t_env	*copy;

	i = -1;
	copy = NULL;
	while (lst != NULL)
		ft_lstadd_back(&copy, lst->data);
	return (copy);
}

/* bulltin echo part 2 */

static int	echo_2(char **tab, int bulltin)
{
	int	i;
	int	x;

	i = bulltin;
	x = 2;
	if (tab[i][0] == '-' && tab[i][1] == 'n')
	{
		while (tab[i][x])
		{
			if (tab[i][x] == 'n')
				x++;
			else
				return (bulltin);
		}
		return (echo_2(tab, bulltin + 1));
	}
	return (bulltin);
}

// bulltin echo //

// no leak //

void	echo(char **tab, int i, int j)
{
	int	bulltin;
	int	in_q;

	bulltin = 0;
	in_q = 0;
	if (tab[i])
	{
		bulltin = echo_2(tab, bulltin);
		if (bulltin > 0)
			i += bulltin;
		while (tab[i])
		{
			j = -1;
			while (tab[i][++j])
				if (!update(tab[i][j], &in_q))
					printf("%c", tab[i][j]);
			if (tab[i])
				printf(" ");
			i++;
		}
	}
	if (bulltin == 0)
		printf("\n");
	check_cmd_is_right(0);
}
