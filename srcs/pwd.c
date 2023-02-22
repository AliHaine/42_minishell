/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <mbouaza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:47:31 by mbouaza           #+#    #+#             */
/*   Updated: 2023/02/22 14:04:49 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* pwd */

void pwd(void)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

/* get the end of the path */

char *g_d_e(void)
{
	char	*path;
	char	*doc;
	int i;
	int x;

	i = 0;
	x = 0;
	path = getcwd(NULL, 0);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	doc = malloc(sizeof(char) * (ft_strlen(path) - i) + 4);
	while(path[i])
		doc[x++] = path[i++];
	doc[x++] = '$';
	doc[x++] = ' ';
	doc[x] = '\0';
	free(path);
	return (doc);
}

// d'autre fonction qui n'ont aucun rapport a pwd //

static int check_quota(char *s)
{
    int i;
    int j;
    int x;

    i = 0;
    x = ft_strlen(s) - 1;
    j = 0;
    if (s[i] && s[i] == '"')
    {
        while (s[i] && s[i] == '"')
            i++;
        while (s[x] && s[x] == '"')
        {
            j++;
            x--;
        }
    }
    else if (s[i] && s[i] == '\'')
    {
        while (s[i] && s[i] == '\'')
            i++;
        while (s[x] && s[x] == '\'')
        {
            j++;
            x--;
        }
    }
    if (i % 2 == 0 && i == j)
    {
        if ((s[x] == '\'' && s[i] == '\'') || (s[x] == '"' && s[i] == '"'))
            return (2);
        else
            return (0);
    }
    else
        return (1);
}

/* trime_quotation : en cour */

/* cas a gerer

- echo oui = oui TRUE

- echo "oui" = oui TRUE

- echo '"oui"' = "oui" TRUE

- echo "'oui'" = 'oui' TRUE

- echo ''"oui"'' = oui TRUE

- echo ""'oui'"" = seg fault FALSE

echo x"oui" = xoui FALSE

*/

/*
void trime_quotation(char *str) 
{
    int i;
    int j;
    int check;
    char *s;

    i = 0;
    check = 0;
    s = ft_strdup(str);
    if (!s)
        return ;
    free(str);
	if (str[i] && str[i] == '"' )
        str = ft_strtrim(s, "\"");
        if (!s)
            return ;
    else if (str[i] && str[i] == '\'')
    {
        str = ft_strtrim(s, "'");
        if (!str)
            return ;
    }
    check = check_quota(s);
    if (check == 0)
        return ;
    else if (str[0] && check == 2)
        trime_quotation(str);
}
*/