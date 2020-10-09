/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:33:22 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 05:50:11 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** Function is call by the MLX on each loop
*/
int			hook_loop(t_data *data)
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

/*
** Function is call by the MLX when a red cross is clicked
*/
int			hook_close(t_data *data)
{
	(void)data;
	mlx_destroy_image(data->mlx, data->img);
	printf("Game Exited\n");
	exit(0);
}

/*
** Function is call by the MLX when a key from keyboard is up
*/
int			hook_keyup(int key_code, t_data *data)
{
	if (valid_key(key_code) && data->key_pressed[(key_code % 14) - 1])
	{
		data->key_pressed[(key_code % 14) - 1] = 0;
		if (!check_keypressed(data))
			data->update = 0;
	}
	return (1);
}

/*
** Function is call by the MLX when a key from keyboard is down
*/
int			hook_keydown(int key_code, t_data *data)
{
	if (valid_key(key_code) && data->key_pressed[(key_code % 14) - 1] == 0)
	{
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