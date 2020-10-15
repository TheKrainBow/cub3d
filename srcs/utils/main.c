/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 05:24:35 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		swap_images(t_data *data)
{
	void	*img_temp;
	void	*draw_temp;

	img_temp = data->img;
	draw_temp = data->draw;
	data->img = data->img2;
	data->draw = data->draw2;
	data->img2 = img_temp;
	data->draw2 = draw_temp;
}

void		draw_gun(t_data *data);
void		update(t_data *data)
{
	clear_screen(0x0000FF, data);
	draw_screen(data);
	if (data->keys.open_map)
		draw_hud(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->gun[data->test].ptr, 10, 10);
	//mlx_put_image_to_window(data->mlx, data->win, data->gun[6].ptr, 500, 500);
	data->test++;
	if (data->test == 6)
		data->test = 0;
	swap_images(data);
}

void		init_keys(t_data *data)
{
	data->keys.forward = 0;
	data->keys.backward = 0;
	data->keys.move_left = 0;
	data->keys.move_right = 0;
	data->keys.look_left = 0;
	data->keys.look_right = 0;
	data->keys.open_map = 0;
	data->keys.run = 0;
	data->keys.crouch = 0;
	data->keys.jump = 0;
}

int			main(void)
{
	t_data			data;

	data.fd = open("map1.cub", 'r');
	init_mlx(&data);
	init_keys(&data);
	update(&data);
	mlx_loop(data.mlx);
	return (0);
}