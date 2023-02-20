/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouaza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:01:52 by mbouaza           #+#    #+#             */
/*   Updated: 2022/11/24 12:02:27 by mbouaza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/* Creation of my buffer_size, used for read() */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/* include */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* Lib for get_next_line */

// char //

char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

// int //

int		check_newline(char c, char *s);

// size_t //

size_t	ft_strlen(const char *s);

#endif
