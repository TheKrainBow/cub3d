/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 05:02:08 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 20:08:05 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_gun(t_data *data)
{
	int		t;

	data->gun[0].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/0.xpm",
	&data->gun[0].wth, &data->gun[0].lth);
	data->gun[0].tab = (t_pixel *)mlx_get_data_addr(data->gun[0].ptr
	, &t, &t, &t);
	data->gun[1].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/1.xpm", &data->gun[1].wth, &data->gun[1].lth);
	data->gun[1].tab = (t_pixel *)mlx_get_data_addr(data->gun[1].ptr, &t, &t, &t);
	data->gun[2].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/2.xpm", &data->gun[2].wth, &data->gun[2].lth);
	data->gun[2].tab = (t_pixel *)mlx_get_data_addr(data->gun[2].ptr, &t, &t, &t);
	data->gun[3].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/3.xpm", &data->gun[3].wth, &data->gun[3].lth);
	data->gun[3].tab = (t_pixel *)mlx_get_data_addr(data->gun[3].ptr, &t, &t, &t);
	data->gun[4].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/4.xpm", &data->gun[4].wth, &data->gun[4].lth);
	data->gun[4].tab = (t_pixel *)mlx_get_data_addr(data->gun[4].ptr, &t, &t, &t);
	data->gun[5].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/5.xpm", &data->gun[5].wth, &data->gun[5].lth);
	data->gun[5].tab = (t_pixel *)mlx_get_data_addr(data->gun[5].ptr, &t, &t, &t);
	data->gun[6].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/Magic/6.xpm", &data->gun[6].wth, &data->gun[6].lth);
	data->gun[6].tab = (t_pixel *)mlx_get_data_addr(data->gun[6].ptr, &t, &t, &t);
	data->health.ptr = mlx_xpm_file_to_image(data->mlx, "./texture/health_bar.xpm", &data->health.wth, &data->health.lth);
	data->health.tab = (t_pixel *)mlx_get_data_addr(data->health.ptr, &t, &t, &t);
}

void	init_mlx(t_data *data)
{
	int		t;

	data->mlx = mlx_init();
	init_parsing(data);
	mlx_get_screen_size(data->mlx, &(data->max_x), &(data->max_y));
	parsing(data);
	if (!data->save)
		data->win = mlx_new_window(data->mlx, data->r.x, data->r.y, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->r.x, data->r.y);
	data->draw = (t_pixel *)mlx_get_data_addr(data->img, &t, &t, &t);
	if (!data->save)
	{
		data->img2 = mlx_new_image(data->mlx, data->r.x, data->r.y);
		data->draw2 = (t_pixel *)mlx_get_data_addr(data->img2, &t, &t, &t);
		mlx_hook(data->win, 17, 1L << 17, hook_close, data);
		mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
		mlx_hook(data->win, 3, 1L << 1, hook_keyup, data);
		mlx_loop_hook(data->mlx, hook_loop, data);
	}
	init_data(data);
	init_gun(data);
}

void	init_parsing(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 5)
		data->pars.t[i] = 0;
	data->pars.f = 0;
	data->pars.c = 0;
	data->pars.r = 0;
	data->pars.player = 0;
}

void	init_data(t_data *data)
{
	if (!(data->distance = malloc(sizeof(double) * (data->r.x + 1))))
		return ;
	if (!(data->ray_bounced = malloc(sizeof(t_point) * (data->r.x + 1))))
		return ;
	if (!(data->ray_inter = malloc(sizeof(t_point) * (data->r.x + 1))))
		return ;
	data->fov = FOV;
	data->average = 0;
	data->player.jump = 0;
}
