/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:33:22 by magostin          #+#    #+#             */
/*   Updated: 2020/12/03 16:54:32 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			hook_loop(t_data *data)
{
	(void)data;
	move_player(data);
	update(data);
	return (0);
}

int			hook_keyup(int key_code, t_data *data)
{
	if (key_code == FORWARD)
		data->keys.forward = 0;
	if (key_code == BACKWARD)
		data->keys.backward = 0;
	if (key_code == LEFT)
		data->keys.move_left = 0;
	if (key_code == RIGHT)
		data->keys.move_right = 0;
	if (key_code == ARR_L)
		data->keys.look_left = 0;
	if (key_code == ARR_R)
		data->keys.look_right = 0;
	if (key_code == RUN)
		data->keys.run = 0;
	if (key_code == CROUCH)
		data->keys.crouch = 0;
	return (1);
}

void		hook_keydown_move(int key_code, t_data *data)
{
	if (key_code == FORWARD)
		data->keys.forward = 1;
	if (key_code == BACKWARD)
		data->keys.backward = 1;
	if (key_code == LEFT)
		data->keys.move_left = 1;
	if (key_code == RIGHT)
		data->keys.move_right = 1;
	if (key_code == ARR_L)
		data->keys.look_left = 1;
	if (key_code == ARR_R)
		data->keys.look_right = 1;
}

int			hook_keydown(int key_code, t_data *data)
{
	hook_keydown_move(key_code, data);
	if (key_code == MAP)
		data->keys.open_map = data->keys.open_map == 1 ? 0 : 1;
	if (key_code == RUN)
		data->keys.run = 1;
	if (key_code == JUMP)
		data->keys.jump = 1;
	if (key_code == FIRE)
		data->keys.shoot = 1;
	if (key_code == CROUCH)
		data->keys.crouch = 1;
	if (key_code == QUIT)
		mlx_loop_end(data->mlx);
	return (1);
}
