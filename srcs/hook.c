/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:19:46 by magostin          #+#    #+#             */
/*   Updated: 2020/09/24 12:24:24 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"


int			hook_loop (t_data *data)
{
	(void)data;
	return (1);
}

int			hook_close(t_data *data)
{
	(void)data;
	mlx_destroy_image(data->mlx, data->img);
	printf("Game Exited\n");
	exit(0);
}

int			hook_keydown(int key_code, t_data *data)
{
	t_point a;

	if (key_code == 32)
	{
		mlx_destroy_window(data->mlx, data->win);
		hook_close(data);
	}
	if (key_code == ARR_L || key_code == ARR_R)
	{
		data->player.angle = key_code == ARR_L ? data->player.angle - 3 : data->player.angle + 3;
		round_angle(&data->player.angle);
	}
	if (key_code == KEY_Z)
	{
		if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x + (cos(data->player.angle * (PI / 180)) / 5))] != '1')
			data->player.pos.x += (cos(data->player.angle * (PI / 180)) / 10);
		if (data->game[(int)(data->player.pos.y + (sin(data->player.angle * (PI / 180)) / 5))][(int)data->player.pos.x] != '1')
			data->player.pos.y += (sin(data->player.angle * (PI / 180)) / 10);
	}
	if (key_code == KEY_S)
	{
		if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x - (cos(data->player.angle * (PI / 180)) / 5))] != '1')
			data->player.pos.x -= (cos(data->player.angle * (PI / 180)) / 10);
		if (data->game[(int)(data->player.pos.y - (sin(data->player.angle * (PI / 180)) / 5))][(int)data->player.pos.x] != '1')
			data->player.pos.y -= (sin(data->player.angle * (PI / 180)) / 10);
	}
	if (key_code == KEY_D)
	{
		if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x + (cos((data->player.angle + 90) * (PI / 180)) / 5))] != '1')
			data->player.pos.x += (cos((data->player.angle + 90) * (PI / 180)) / 10);
		if (data->game[(int)(data->player.pos.y + (sin((data->player.angle + 90) * (PI / 180)) / 5))][(int)data->player.pos.x] != '1')
			data->player.pos.y += (sin((data->player.angle + 90) * (PI / 180)) / 10);
	}
	if (key_code == KEY_Q)
	{
		if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x - (cos((data->player.angle + 90) * (PI / 180)) / 5))] != '1')
			data->player.pos.x -= (cos((data->player.angle + 90) * (PI / 180)) / 10);
		if (data->game[(int)(data->player.pos.y - (sin((data->player.angle + 90) * (PI / 180)) / 5))][(int)data->player.pos.x] != '1')
			data->player.pos.y -= (sin((data->player.angle + 90) * (PI / 180)) / 10);
	}
	if (data->update == 1)
		update(data);
	//printf("%f\n", data->player.angle);
	return (1);
}
