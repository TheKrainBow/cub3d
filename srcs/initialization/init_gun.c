/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:12:45 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 20:13:36 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_gun_ptr(t_data *data)
{
	data->gun[0].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/0.xpm", &data->gun[0].wth, &data->gun[0].lth);
	data->gun[1].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/1.xpm", &data->gun[1].wth, &data->gun[1].lth);
	data->gun[2].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/2.xpm", &data->gun[2].wth, &data->gun[2].lth);
	data->gun[3].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/3.xpm", &data->gun[3].wth, &data->gun[3].lth);
	data->gun[4].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/4.xpm", &data->gun[4].wth, &data->gun[4].lth);
	data->gun[5].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/5.xpm", &data->gun[5].wth, &data->gun[5].lth);
	data->gun[6].ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/Magic/6.xpm", &data->gun[6].wth, &data->gun[6].lth);
	data->health.ptr = mlx_xpm_file_to_image(data->mlx,
	"./texture/health_bar.xpm", &data->health.wth, &data->health.lth);
}

void	init_gun_tab(t_data *data)
{
	int		t;

	data->gun[0].tab = (t_pixel *)mlx_get_data_addr(data->gun[0].ptr,
	&t, &t, &t);
	data->gun[1].tab = (t_pixel *)mlx_get_data_addr(data->gun[1].ptr,
	&t, &t, &t);
	data->gun[2].tab = (t_pixel *)mlx_get_data_addr(data->gun[2].ptr,
	&t, &t, &t);
	data->gun[3].tab = (t_pixel *)mlx_get_data_addr(data->gun[3].ptr,
	&t, &t, &t);
	data->gun[4].tab = (t_pixel *)mlx_get_data_addr(data->gun[4].ptr,
	&t, &t, &t);
	data->gun[5].tab = (t_pixel *)mlx_get_data_addr(data->gun[5].ptr,
	&t, &t, &t);
	data->gun[6].tab = (t_pixel *)mlx_get_data_addr(data->gun[6].ptr,
	&t, &t, &t);
	data->health.tab = (t_pixel *)mlx_get_data_addr(data->health.ptr,
	&t, &t, &t);
}

void	init_gun(t_data *data)
{
	init_gun_ptr(data);
	init_gun_tab(data);
}