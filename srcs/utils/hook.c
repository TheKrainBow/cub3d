/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:33:22 by magostin          #+#    #+#             */
/*   Updated: 2020/11/27 19:49:37 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Function is call by the MLX on each loop
*/
int			hook_loop(t_data *data)
{
	(void)data;
	move_player(data);
	update(data);
	return (0);
}

/*
** Function is call by the MLX when a red cross is clicked
*/
int			hook_close(t_data *data)
{
	(void)data;
	//mlx_destroy_image(data->mlx, data->img);
	printf("Game Exited\n");
	exit(0);
}

/*
** Function is call by the MLX when a key from keyboard is up
*/
int			hook_keyup(int key_code, t_data *data)
{
	if (key_code == KEY_Z)
		data->keys.forward = 0;
	if (key_code == KEY_S)
		data->keys.backward = 0;
	if (key_code == KEY_Q)
		data->keys.move_left = 0;
	if (key_code == KEY_D)
		data->keys.move_right = 0;
	if (key_code == ARR_L)
		data->keys.look_left = 0;
	if (key_code == ARR_R)
		data->keys.look_right = 0;
	if (key_code == SHIFT)
		data->keys.run = 0;
	if (key_code == CTRL)
		data->keys.crouch = 0;
	return (1);
}

/*
** Function is call by the MLX when a key from keyboard is down
*/
int			hook_keydown(int key_code, t_data *data)
{
	if (key_code == KEY_Z)
		data->keys.forward = 1;
	if (key_code == KEY_S)
		data->keys.backward = 1;
	if (key_code == KEY_Q)
		data->keys.move_left = 1;
	if (key_code == KEY_D)
		data->keys.move_right = 1;
	if (key_code == ARR_L)
		data->keys.look_left = 1;
	if (key_code == ARR_R)
		data->keys.look_right = 1;
	if (key_code == 109)
		data->keys.open_map = data->keys.open_map == 1 ? 0 : 1;
	if (key_code == SHIFT)
		data->keys.run = 1;
	if (key_code == SPACE)
		data->keys.jump = 1;
	if (key_code == F)
		data->keys.shoot = 1;
	if (key_code == CTRL)
		data->keys.crouch = 1;
	if (key_code == QUIT)
	{
		mlx_destroy_window(data->mlx, data->win);
		hook_close(data);
	}
	return (1);
}