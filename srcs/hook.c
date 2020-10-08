/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:19:46 by magostin          #+#    #+#             */
/*   Updated: 2020/10/08 16:35:27 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"

int			check_keypressed(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 12)
		if (data->key_pressed[i])
			return (1);
	return (0);
}

void		move_player(t_data *data)
{
	t_point		check;

	check.x = (cos(data->player.angle * (PI / 180)) / 5) * data->key_pressed[KEY_Z % 14 - 1] +
			(-cos(data->player.angle * (PI / 180)) / 5) * data->key_pressed[KEY_S % 14 - 1] +
			(cos((data->player.angle + 90) * (PI / 180)) / 5) * data->key_pressed[KEY_D % 14 - 1] + 
			(-cos((data->player.angle + 90) * (PI / 180)) / 5) * data->key_pressed[KEY_Q % 14 - 1];
	check.y = (sin(data->player.angle * (PI / 180)) / 5) * data->key_pressed[KEY_Z % 14 - 1] +
			(-sin(data->player.angle * (PI / 180)) / 5) * data->key_pressed[KEY_S % 14 - 1] +
			(sin((data->player.angle + 90) * (PI / 180)) / 5) * data->key_pressed[KEY_D % 14 - 1] + 
			(-sin((data->player.angle + 90) * (PI / 180)) / 5) * data->key_pressed[KEY_Q % 14 - 1];
	if (data->game[(int)data->player.pos.y][(int)(data->player.pos.x + check.x)] != '1')
		data->player.pos.x +=
			(cos(data->player.angle * (PI / 180)) / (100000 - 70000 * data->key_pressed[SHIFT % 14 - 1])) * data->key_pressed[KEY_Z % 14 - 1] +
			(-cos(data->player.angle * (PI / 180)) / (100000)) * data->key_pressed[KEY_S % 14 - 1] +
			(cos((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_D % 14 - 1] + 
			(-cos((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_Q % 14 - 1];
	if (data->game[(int)(data->player.pos.y + check.y)][(int)data->player.pos.x] != '1')
		data->player.pos.y +=
			(sin(data->player.angle * (PI / 180)) / (100000 - 70000 * data->key_pressed[SHIFT % 14 - 1])) * data->key_pressed[KEY_Z % 14 - 1] +
			(-sin(data->player.angle * (PI / 180)) / (100000)) * data->key_pressed[KEY_S % 14 - 1] +
			(sin((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_D % 14 - 1] + 
			(-sin((data->player.angle + 90) * (PI / 180)) / (100000)) * data->key_pressed[KEY_Q % 14 - 1];
	if (data->key_pressed[ARR_R % 14 - 1] || data->key_pressed[ARR_L % 14 - 1])
	{
		data->player.angle = data->key_pressed[ARR_L % 14 - 1] ? data->player.angle - 0.00025 : data->player.angle + 0.00025;
		round_angle(&data->player.angle);
	}
}

int			hook_loop (t_data *data)
{
	(void)data;
	if (data->update)
	{
		data->tick++;
		move_player(data);
		if (data->tick > 10000)
		{
			update(data);
			data->tick = 0;
		}
	}
	//update(data);
	return (0);
}

int			hook_close(t_data *data)
{
	(void)data;
	mlx_destroy_image(data->mlx, data->img);
	printf("Game Exited\n");
	exit(0);
}

int			valid_key(int key_code)
{
	return (key_code == KEY_Z
	|| key_code == KEY_Q
	|| key_code == KEY_S
	|| key_code == KEY_D
	|| key_code == ARR_L
	|| key_code == ARR_R
	|| key_code == SPACE
	|| key_code == SHIFT);
}

int			hook_keyup(int key_code, t_data *data)
{
	if (valid_key(key_code) && data->key_pressed[(key_code % 14) - 1])
	{
		data->key_pressed[(key_code % 14) - 1] = 0;
		/*if (key_code == SHIFT)
			update(data);*/
		if (!check_keypressed(data))
			data->update = 0;
	}
	return (1);
}

int			hook_keydown(int key_code, t_data *data)
{
	t_point a;

	//printf("%d => %d\n", key_code, (key_code % 14) - 1);
	if (valid_key(key_code) && data->key_pressed[(key_code % 14) - 1] == 0)
	{
		//printf("SHIFT\n");
		data->update = 1;
		data->key_pressed[(key_code % 14) - 1] = 1;
	}
	if (key_code == 32)
	{
		mlx_destroy_window(data->mlx, data->win);
		hook_close(data);
	}
	//update(data);
	return (1);
}
