/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:13:58 by magostin          #+#    #+#             */
/*   Updated: 2020/11/23 19:10:33 by magostin         ###   ########.fr       */
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

char		*ft_itoa(int n);
void		ft_save(t_data *data)
{
	int		fd;
	int		x;
	int		y;
	int		i;
	int		bpp;
	int		*tmp;

	tmp = (int *)mlx_get_data_addr(data->img, &bpp, &x, &x);
	i = 0;
	fd = -1;
	while (fd == -1)
	{
		//fd = open(ft_strjoin(ft_strjoin("./save_", ft_itoa(i)), ".bmp"), O_CREAT | O_RDWR);
		fd = open("./save.bmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		i++;
	}
	save_header(fd, bpp, data);
	y = data->r.y;
	while (y >= 0)
	{
		x = 0;
		while (x < data->r.x)
		{
			write(fd, &tmp[y * ((int)data->r.x) + x], 4);
			x++;
		}
		y--;
	}
}