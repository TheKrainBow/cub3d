/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:30:33 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:21:17 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"


void		update(t_data *data)
{
	draw_screen(data);
	draw_hud(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->update = 1;
}

void		init_keys(t_data *data)
{
	int		i;
	
	i = -1;
	while (++i < 12)
		data->key_pressed[i] = 0;
	return ;
}

int			main(void)
{
	t_data			data;
	int 			trash;

	data.fd = open("map1.cub", 'r');
	init_mlx(&data);
	data.sprt.ptr = mlx_xpm_file_to_image(data.mlx, "./texture/shrek.xpm", &(data.sprt.wth), &(data.sprt.lth));
	data.sprt.tab = (unsigned int *)mlx_get_data_addr(data.sprt.ptr, &trash, &trash, &trash);
	init_keys(&data);
	update(&data);
	mlx_loop(data.mlx);
	return (0);
}