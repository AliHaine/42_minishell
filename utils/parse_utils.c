//
// Created by Ali Yagmur on 3/24/23.
//

#include "../minishell.h"

char	*get_current_word(char *s, int *a)
{
	int	i;
	char *new;

	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a])
		   && s[*a] != '|')
	{
		i++;
		*a = *a + 1;
	}
	new = malloc(sizeof(char) * i + 1);
	*a = *a - i;
	i = 0;
	while (s[*a] && s[*a] != ' ' && s[*a] != is_redir_char(s[*a])
		   && s[*a] != '|')
	{
		new[i++] = s[*a];
		*a = *a + 1;
	}
	new[i] = '\0';
	return (new);
}

char *ft_strjoin_parse(char *s1, char *s2)
{
	int	a;
	int b;
	char *new;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (0);
	new = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new)
		return (0);
	while (s1[a])
	{
		new[a] = s1[a];
		a++;
	}
	new[a++] = ' ';
	while (s2[b])
		new[a++] = s2[b++];
	new[a] = '\0';
	//free(s1);
	return (new);
}
