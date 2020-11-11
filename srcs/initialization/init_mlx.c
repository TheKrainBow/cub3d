/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 05:02:08 by magostin          #+#    #+#             */
/*   Updated: 2020/10/27 07:59:34 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
void	scale_texture_to_res(int i, t_data *data)
{
	void			*img;
	unsigned int	*draw;
}
*/
void	init_gun(t_data *data)
{
	int		t;

	data->gun[0].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun0.xpm", &data->gun[0].wth, &data->gun[0].lth);
	data->gun[0].tab = (t_pixel *)mlx_get_data_addr(data->gun[0].ptr, &t, &t, &t);
	data->gun[1].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun1.xpm", &data->gun[1].wth, &data->gun[1].lth);
	data->gun[1].tab = (t_pixel *)mlx_get_data_addr(data->gun[1].ptr, &t, &t, &t);
	data->gun[2].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun2.xpm", &data->gun[2].wth, &data->gun[2].lth);
	data->gun[2].tab = (t_pixel *)mlx_get_data_addr(data->gun[2].ptr, &t, &t, &t);
	data->gun[3].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun3.xpm", &data->gun[3].wth, &data->gun[3].lth);
	data->gun[3].tab = (t_pixel *)mlx_get_data_addr(data->gun[3].ptr, &t, &t, &t);
	data->gun[4].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun4.xpm", &data->gun[4].wth, &data->gun[4].lth);
	data->gun[4].tab = (t_pixel *)mlx_get_data_addr(data->gun[4].ptr, &t, &t, &t);
	data->gun[5].ptr = mlx_xpm_file_to_image(data->mlx, "./texture/gun5.xpm", &data->gun[5].wth, &data->gun[5].lth);
	data->gun[5].tab = (t_pixel *)mlx_get_data_addr(data->gun[5].ptr, &t, &t, &t);
}

/*
** initialize all mlx ptr and pars .cub
*/
void	init_mlx(t_data *data)
{
	int		t;

	data->mlx = mlx_init();
	init_parsing(data);
	mlx_get_screen_size(data->mlx, &(data->max_x), &(data->max_y));
	parsing(data);
	data->win = mlx_new_window(data->mlx, data->r.x, data->r.y, "Cub3D");
	data->img = mlx_new_image(data->mlx, data->r.x, data->r.y);
	data->draw = (t_pixel *)mlx_get_data_addr(data->img, &t, &t, &t);
	data->img2 = mlx_new_image(data->mlx, data->r.x, data->r.y);
	data->draw2 = (t_pixel *)mlx_get_data_addr(data->img2, &t, &t, &t);
	mlx_hook(data->win, 17, 1L << 17, hook_close, data);
	mlx_hook(data->win, 2, 1L << 0, hook_keydown, data);
	mlx_hook(data->win, 3, 1L << 1, hook_keyup, data);
	mlx_loop_hook(data->mlx, hook_loop, data);
	init_data(data);
	init_gun(data);
}
/*
** initialize parsing structure
*/
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

/*
** initialize data
*/
void	init_data(t_data *data)
{
	if (!(data->distance = malloc(sizeof(double) * (data->r.x + 1))))
		return ;
	if (!(data->ray_bounced = malloc(sizeof(t_point) * (data->r.x + 1))))
		return ;
	if (!(data->ray_inter = malloc(sizeof(t_point) * (data->r.x + 1))))
		return ;
	//data->objs = create_wall(data);
	data->fov = FOV;
	data->average = 0;
	data->update = 0;
	data->tick = 0;
	data->player.jump = 0;
}