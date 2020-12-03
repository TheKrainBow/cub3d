/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:52:24 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 16:58:36 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_strchr(char *buffer, char chr)
{
	int		pos;

	pos = 0;
	while (buffer[pos] && buffer[pos] != chr)
		pos++;
	return (buffer[pos] == chr ? pos + 1 : -1);
}

static int		ft_read(int fd, char *buffer, char **line)
{
	char	*tmp;
	int		chr_read;
	int		pos;

	while ((chr_read = read(fd, buffer, BUFFER_SIZE)) && chr_read != -1)
	{
		buffer[chr_read] = 0;
		tmp = ft_strjoin(*line, buffer);
		free(*line);
		*line = tmp;
		if ((pos = ft_strchr(buffer, '\n')) != -1)
		{
			ft_memmove(buffer, buffer + pos, BUFFER_SIZE - pos);
			buffer[BUFFER_SIZE - pos] = 0;
			break ;
		}
	}
	return (chr_read == 0 || chr_read == -1 ? chr_read : 1);
}

int				get_next_line(int fd, char **line)
{
	static char		buffer[100][BUFFER_SIZE + 1];
	int				pos;

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = buffer[fd][0] ? ft_strdup(buffer[fd]) : ft_strdup("");
	if (!*line)
		return (-1);
	if (!(buffer[fd][0]))
		return (ft_read(fd, buffer[fd], line));
	if ((pos = ft_strchr(buffer[fd], '\n')) == -1)
		return (ft_read(fd, buffer[fd], line));
	ft_memmove(buffer[fd], buffer[fd] + pos, BUFFER_SIZE - pos);
	return (1);
}
