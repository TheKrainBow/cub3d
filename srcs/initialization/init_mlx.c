/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 05:02:08 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:11:28 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** initialize all mlx ptr and pars .cub
*/
void	init_mlx(t_data *data)
{
	int		t;

	data->mlx = mlx_init();
	if (parsing(data) == 0)
		exit(0);
	data->win = mlx_new_window(data->mlx, data->r.x, data->r.y, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->r.x, data->r.y);
	data->draw = (unsigned int *)mlx_get_data_addr(data->img, &t, &t, &t);
	mlx_hook(data->win, 17, 1L << 17, hook_close, data);
	mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
	mlx_hook(data->win, 3, 1L << 1, hook_keyup, data);
	mlx_loop_hook(data->mlx, hook_loop, data);
	init_data(data);
}

/*
** initialize data
*/
void	init_data(t_data *data)
{
	data->fov = FOV;
	if (!(data->distance = malloc(sizeof(double) * data->r.x)))
		return ;
	data->objs = create_wall(data);
	data->average = 0;
	data->update = 0;
	data->tick = 0;
}