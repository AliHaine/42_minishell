/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:04:08 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/24 17:53:43 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	malloc_for_quotation(char const *str)
{
	int	count;
	int	i;
	int	quote1;
	int	quote2;

	i = 0;
	count = 0;
	quote1 = 0;
	quote2 = 0;
	while (str && str[i])
	{
		quote2 = (quote2 + (!quote1 && str[i] == '\'')) % 2;
		quote1 = (quote1 + (!quote2 && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !quote2) || (str[i] == '\'' && !quote1))
			count++;
		i++;
	}
	if (quote2 || quote1)
		return (-1);
	return (count);
}

char	*ft_strtrim_quot(char const *str, int quote2, int quote1)
{
	int		count;
	int		i[2];
	char	*str_trim;

	i[1] = -1;
	i[0] = 0;
	count = malloc_for_quotation((char *)str);
	if (!str || count == -1)
		return (NULL);
	str_trim = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!str_trim)
		return (NULL);
	while (str[i[0]])
	{
		quote2 = (quote2 + (!quote1 && str[i[0]] == '\'')) % 2;
		quote1 = (quote1 + (!quote2 && str[i[0]] == '\"')) % 2;
		if ((str[i[0]] != '\"' || quote2) && (str[i[0]] != '\'' || quote1) \
			&& ++i[1] >= 0)
			str_trim[i[1]] = str[i[0]];
		i[0]++;
	}
	str_trim[++i[1]] = '\0';
	return (str_trim);
}