/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 05:02:08 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 20:12:56 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
