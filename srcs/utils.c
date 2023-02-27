#include "../minishell.h"

/* ft_strchr */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 256)
	{
		c = c - 256;
	}
	while (s[i])
	{
		if (s[i] == c)
		{
			return (&((char *)s)[i]);
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/* ft_strrchr */

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/* ft_substr */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

/* ft_strtrim */

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (set == NULL || s1 == NULL)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j && ft_strrchr(set, s1[j]))
		j--;
	j = (j - i) + 1;
	return (ft_substr(s1, i, j));
}

// ft_strcmp //

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	while (a[i])
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}