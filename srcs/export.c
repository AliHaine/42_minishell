/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:37:17 by mbouaza           #+#    #+#             */
/*   Updated: 2023/04/13 00:32:52 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// no leaks //

static void	export_and_nothing(t_env *list, int i, int j)
{
	char	**sort_env;

	printf("%s\n", list->data);
	sort_env = print_sorted_strings(list, 0, 0);
	while (sort_env[i])
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (sort_env[i][j])
		{
			write(1, &sort_env[i][j], 1);
			if (sort_env[i][j] == '=')
				write(1, "\"", 1);
			j++;
		}
		printf("\"\n");
		i++;
	}
	free_tt(sort_env);
	check_cmd_is_right(0);
}

// export hd=d export hd=ds error //ex

static int	check_valid(char *path)
{
	int		check;
	char	*gde;
	int		i;

	check = 0;
	i = 0;
	gde = g_d_e();
	while (path[i] && path[i] != '=')
	{
		if (char_ccmp(path[i], "\t\n\r@&()[]{}%!<>?-*+^~") == 1)
			check = 2;
		i++;
	}
	if (check == 0 && char_cmp(path, "=") == 1)
		return (free(gde), check_cmd_is_right(0));
	else if (check == 2)
		printf("%s: export: '%s': not a valid identifier\n", gde, path);
	g_ms.stat = 1;
	return (free(gde), check_cmd_is_right(1));
}

void	remplace_env(char **env, char *path)
{
	int	len;
	int	i;

	i = 0;
	while (env[i])
	{
		len = 0;
		while (path[len])
		{
			if (env[i][len] && env[i][len] == path[len])
				len++;
			else
				break ;
			if (path[len] && env[i][len] == '=')
			{
				free(env[i]);
				env[i] = ft_strdup(path);
			}
		}
		i++;
	}
	return ;
}

void	remplace_lst(t_env *lst, char *path)
{
	int	len;
	int	i;

	i = 0;
	while (lst != NULL)
	{
		len = 0;
		while (path[len])
		{
			if (lst->data[len] && lst->data[len] == path[len])
				len++;
			else
				break ;
			if (path[len] && lst->data[len] == '=')
			{
				free(lst->data);
				lst->data = ft_strdup(path);
			}
		}
		i++;
		lst = lst->next;
	}
	return ;
}

// leaks tu coco

void	export(char **arg, t_env *list, int i)
{	
	if (!arg[i])
		export_and_nothing(list, 0, 0);
	while (arg[i])
	{
		if (check_path_lst(arg[i], list, 0) == 1)
			remplace_lst(list, arg[i]);
		else
		{
			if (check_valid(arg[i]) == 0)
				add_env_var(&list, arg[i]);
		}
		i++;
	}
	check_cmd_is_right(g_ms.stat);
}
