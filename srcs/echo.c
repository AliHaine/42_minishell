/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:18:28 by mbouaza           #+#    #+#             */
/*   Updated: 2023/05/01 04:34:31 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lst_copy_tab(char **env)
{
	int		i;
	t_env	*lst;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	free(pwd);
	i = -1;
	lst = NULL;
	while (env[++i])
		ft_lstadd_back(&lst, env[i]);
	return (lst);
}

/* bulltin echo part 2 */

// refaire echo en char *

static int	echo_2(char *line, int *bulltin, int i)
{
	int	j;

	j = 0;
	if (line[i] == '-' && line[i + 1] == 'n')
	{
		j += 1;
		while (line[i + j] == 'n')
			j++;
		if (line[i + j] == ' ' || !line[i + j])
		{
			while (line[i + j] && line[i + j] == ' ')
				j++;
			i += j;
			*bulltin = 1;
		}
		else
			return (i);
		return (echo_2(line, bulltin, i));
	}
	return (i);
}

static char	*new_echo_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	i += 4;
	while (line[i] == ' ')
		i++;
	new = malloc(sizeof(char) * (ft_strlen(line) - i) + 1);
	while (line[i])
		new[j++] = line[i++];
	new[j] = '\0';
	return (new);
}

// bulltin echo //

void	echo(char *echo_line, int i)
{
	int		bulltin;
	int		size;
	char	*line;

	bulltin = 0;
	size = 0;
	line = new_echo_line(echo_line);
	if (line[i])
	{
		size = echo_2(line, &bulltin, 0);
		i = size;
		while (line[i])
			printf("%c", line[i++]);
	}
	if (bulltin == 0)
		printf("\n");
	check_cmd_is_right(0);
	free(line);
}
