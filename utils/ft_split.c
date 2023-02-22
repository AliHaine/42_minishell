#include "../minishell.h"

// ft_strdup //

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dest;

	len = ft_strlen(s1);
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// ft_substr_can_free //

static char	*ft_substr_can_free(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

// free_all  //

static void	*free_all(char **tab, int w)
{
	int	i;

	i = 0;
	while (i != w)
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

// ft_count_word //

static int	ft_count_word(char *s, char c)
{
	char	str;
	int		i;
	int		j;

	str = c;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (str == c && s[i] != c)
		{
			j++;
		}
		str = s[i];
		i++;
	}
	return (j);
}

// ft_split //

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		word;
	int		i;
	int		j;

	word = 0;
	i = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!tab)
		return (0);
	while (s[j] && s[i] && word < ft_count_word(s, c))
	{
		i = j;
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		tab[word++] = ft_substr_can_free(s, i, j - i);
		if (!tab[word - 1])
			return (free_all(tab, word));
	}
	tab[word] = NULL;
	return (tab);
}