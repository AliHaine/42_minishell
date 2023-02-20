/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:56:38 by ayagmur           #+#    #+#             */
/*   Updated: 2022/11/20 12:56:39 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_size(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (i == 1)
		i = 0;
	if (tmp[i] != '\n')
	{
		if (i > 0)
			i--;
	}
	return (i);
}

static char	*next_line(char *tmp, int i)
{
	int		j;
	char	*line;

	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
	{
		free(tmp);
		return (0);
	}
	line = ft_calloc((ft_strlen(tmp) - i) + 1, sizeof(char));
	if (line == NULL)
	{
		free(tmp);
		return (0);
	}
	i++;
	j = 0;
	while (tmp[i])
		line[j++] = tmp[i++];
	line[j] = '\0';
	free(tmp);
	return (line);
}

static char	*read_file(int fd, char *tmp)
{
	char	*buffer;
	int		read_ret;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (0);
	read_ret = 1;
	while (read_ret > 0)
	{
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret < 0)
		{
			free(buffer);
			return (0);
		}
		buffer[read_ret] = '\0';
		tmp = ft_strjoin(tmp, buffer);
		if (tmp == NULL)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (tmp);
}

static char	*get_line(char *line, char *tmp, int i)
{
	i = get_size(tmp);
	line = ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
	{
		free(tmp);
		return (0);
	}
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*tmp = 0;
	char		*line;
	int			i;

	line = 0;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	tmp = read_file(fd, tmp);
	if (!tmp)
		return (0);
	line = get_line(line, tmp, i);
	tmp = next_line(tmp, i);
	if (line[i] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
