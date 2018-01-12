/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:28:10 by cababou           #+#    #+#             */
/*   Updated: 2018/01/12 19:10:08 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

static char		*g_str;
static int		g_is_initialized = 0;
static size_t	g_nextline = 0;

int		readfile(const int fd)
{
	char	*strbuffer;
	int		bytesread;

	strbuffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (strbuffer == NULL)
		return (0);
	while ((bytesread = read(fd, strbuffer, BUFF_SIZE)) > 0)
	{
		strbuffer[bytesread] = '\0';
		g_str = ft_strjoin(g_str, strbuffer);
	}
	if (bytesread == -1 && errno == EBADF)
		return (0);
	return (1);
}

char	*ft_getline(size_t line)
{
	size_t i;
	size_t cpystart;
	size_t currentline;

	i = 0;
	cpystart = 0;
	currentline = 0;
	while (1)
	{
		if (g_str[i] == '\0')
		{
			if (currentline != line || cpystart == i)
				return (NULL);
			else
				return (ft_strsub(g_str, cpystart, i - cpystart));
		}
		if (g_str[i] == '\n')
		{
			if (currentline == line)
				return (ft_strsub(g_str, cpystart, i - cpystart));
			currentline++;
			cpystart = i + 1;
		}
		i++;
	}
}

int		get_next_line(const int fd, char **line)
{
	if (fd < 0)
		return (-1);
	if (!g_is_initialized)
	{
		g_str = ft_strnew(0);
		if (readfile(fd))
			g_is_initialized = 1;
		else
			return (-1);
	}
	if (((*line) = ft_getline(g_nextline)) != NULL)
	{
		g_nextline++;
		return (1);
	}
	return (0);
}
