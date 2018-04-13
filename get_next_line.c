/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:28:10 by cababou           #+#    #+#             */
/*   Updated: 2018/04/13 02:34:59 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

void	*get_file_by_descriptor(t_lstcontainer *files, int fd, int which)
{
	int		i;
	void	*tmp_file;

	i = 0;
	while (i < files->size(files))
	{
		if (which == 0)
		{
			tmp_file = ft_lstget(i, files->firstelement)->content;
			if (((t_file *)tmp_file)->file_descriptor == fd)
				return (tmp_file);
		}
		else if (which == 1)
		{
			tmp_file = ft_lstget(i, files->firstelement);
			return (tmp_file);
		}
		i++;
	}
	return (NULL);
}

int		read_file(t_file *file)
{
	char	*strbuffer;
	int		bytesread;

	strbuffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (strbuffer == NULL)
		return (0);
	while ((bytesread = read(file->file_descriptor, strbuffer, BUFF_SIZE)) > 0)
	{
		strbuffer[bytesread] = '\0';
		file->content = ft_strjoin(file->content, strbuffer, 0);
	}
	if (bytesread == -1 && errno == EBADF)
		return (0);
	return (1);
}

char	*ft_getline(t_file *file)
{
	size_t i;
	size_t cpystart;
	size_t currentline;

	i = 0;
	cpystart = 0;
	currentline = 0;
	while (1)
	{
		if (file->content[i] == '\0')
		{
			if (currentline != file->next_line || cpystart == i)
				return (NULL);
			else
				return (ft_strsub(file->content, cpystart, i - cpystart, 0));
		}
		if (file->content[i] == '\n')
		{
			if (currentline == file->next_line)
				return (ft_strsub(file->content, cpystart, i - cpystart, 0));
			currentline++;
			cpystart = i + 1;
		}
		i++;
	}
}

char	*ft_getnextline(t_file *file)
{
	int		i;
	char	*tmp_str;

	i = file->next_start;
	while (1)
	{
		if (file->content[i] == '\0')
		{
			if (i == file->next_start)
				return (NULL);
			else
			{
				tmp_str = ft_strsub(file->content, file->next_start, i - file->next_start, 0);
				file->next_start = i;
				return (tmp_str);
			}
		}
		if (file->content[i] == '\n')
		{
			tmp_str = ft_strsub(file->content, file->next_start, i - file->next_start, 0);
			file->next_start = i + 1;
			return (tmp_str);
		}
		i++;
	}
}

t_file	*initialize(int file_descriptor)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	file->content = ft_strnew(0);
	file->file_descriptor = file_descriptor;
	file->next_line = 0;
	return (file);
}

int		get_next_line(const int fd, char **line)
{
	static t_lstcontainer	*files;
	t_file					*file;

	if (fd < 0)
		return (-1);
	if (files == NULL)
		files = lstcontainer_new();
	file = (t_file *)get_file_by_descriptor(files, fd, 0);
	if (file == NULL)
	{
		if ((file = initialize(fd)) == NULL)
			return (-1);
		if (read_file(file) != 1)
			return (-1);
		files->add(files, file, sizeof(file));
	}
	if (((*line) = ft_getline(file)) != NULL)
	{
		ft_putendl((*line));
		file->next_line++;
		return (1);
	}
	return (0);
}
