/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:43:56 by magostin          #+#    #+#             */
/*   Updated: 2020/07/18 19:55:14 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				read_line(t_nxtlne nxtlne[100], char *buffer, int lnbr)
{
	int		read_return;
	char	*temp;

	read_return = 1;
	while (!(ft_strchr(nxtlne[lnbr].line, '\n')) && read_return)
	{
		read_return = read(nxtlne[lnbr].fd, buffer, 4096);
		if (read_return == -1)
			return (-1);
		if (read_return)
		{
			temp = nxtlne[lnbr].line;
			buffer[read_return] = 0;
			if (!(nxtlne[lnbr].line = ft_strjoin(nxtlne[lnbr].line, buffer)))
				return (0);
			free(temp);
		}
	}
	return (1);
}

char			*stock_line(t_nxtlne nxtlne[100], int lnbr)
{
	char		*buffer;
	char		*dest;
	char		*temp;

	buffer = ft_strchr(nxtlne[lnbr].line, '\n');
	if (buffer)
	{
		if (!(dest = ft_strndup(nxtlne[lnbr].line, buffer - nxtlne[lnbr].line)))
			return (NULL);
		temp = nxtlne[lnbr].line;
		if (!(nxtlne[lnbr].line = ft_strdup(buffer)))
			return (NULL);
		free(temp);
	}
	else
	{
		if (!(dest = ft_strdup(nxtlne[lnbr].line)))
			return (NULL);
		nxtlne[lnbr].line = NULL;
		free(nxtlne[lnbr].line);
	}
	return (dest);
}

int				ft_fd_exist(int fd, t_nxtlne nxtlne[100])
{
	int		i;

	i = 0;
	if (nxtlne[0].fd == 0 && nxtlne[99].fd == 0)
	{
		while (i < 100)
		{
			nxtlne[i].fd = -1;
			i++;
		}
	}
	i = 0;
	while (nxtlne[i].fd != -1 && nxtlne[i].fd != fd)
		i++;
	nxtlne[i].fd = fd;
	return (i);
}

int				get_next_line(int fd, char **line)
{
	static t_nxtlne		nxtlne[100];
	char				*buffer;
	int					lnbr;
	int					error;

	if (4096 <= 0 || !line || fd < 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (4096 + 1))))
		return (-1);
	lnbr = ft_fd_exist(fd, nxtlne);
	error = read_line(nxtlne, buffer, lnbr);
	if (error == -1)
		return (-1);
	if (error == 0)
	{
		*line = NULL;
		return (1);
	}
	free(buffer);
	if (!(*line = stock_line(nxtlne, lnbr)))
		return (-1);
	return (nxtlne[lnbr].line ? 1 : 0);
}/*
#include <stdio.h>

int main(int argc, char **argv)
{
	char		*str = NULL;
	int			fd;
	int			i;
	int			ret;
	char		buffer[10];

	i = 0;
	ret = 1;
	fd = open(argv[argc - 1], 'r');
	while (i < 7)
	{
		ret = get_next_line(fd, &str);
		printf("|%s| %d\n", str, ret);
		i++;
	}
	free(str);
}*/