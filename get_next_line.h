/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 17:40:44 by cababou           #+#    #+#             */
/*   Updated: 2018/04/13 02:32:00 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 16

typedef struct		s_file
{
	char			*content;
	int				file_descriptor;
	size_t			next_line;
	size_t			next_start;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
