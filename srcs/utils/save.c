/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:13:58 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:47:29 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		save_header(int fd, int bpp, t_data *data)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * data->r.x * data->r.y;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	tmp = (int)data->r.x;
	write(fd, &tmp, 4);
	tmp = (int)data->r.y;
	write(fd, &tmp, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	tmp = bpp;
	write(fd, &tmp, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void		ft_save(t_data *data)
{
	int		fd;
	t_point	p;
	int		i;
	int		bpp;
	int		*tmp;

	tmp = (int *)mlx_get_data_addr(data->img, &bpp, &i, &i);
	i = 0;
	fd = -1;
	while (fd == -1)
	{
		fd = open("./save.bmp", O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		i++;
	}
	save_header(fd, bpp, data);
	p.y = data->r.y + 1;
	while (--p.y >= 0)
	{
		p.x = -1;
		while (++p.x < data->r.x)
			write(fd, &tmp[(int)p.y * ((int)data->r.x) + (int)p.x], 4);
	}
}
