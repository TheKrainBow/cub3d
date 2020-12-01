/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:53:53 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:55:10 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	change_p_pos(t_data *data, double angle, double speed)
{
	t_point pos;
	t_point n;

	n.x = cos(ator(angle)) * speed;
	n.y = sin(ator(angle)) * speed;
	pos = data->player.pos;
	if (!ft_strchr("123", data->game[(int)(pos.y)][(int)(pos.x + n.x)]))
		data->player.pos.x += cos(ator(angle)) * (speed * speed);
	if (!ft_strchr("123", data->game[(int)(pos.y + n.y)][(int)(pos.x + n.x)]))
		data->player.pos.y += sin(ator(angle)) * (speed * speed);
}

void	shoot(t_data *data)
{
	t_block		wall;

	wall.dist = 0;
	data->mirrored = 0;
	data->bounced = 0;
	closest_wall_a(fix_angle(data->player.angle), data->player.pos, wall, data);
	while (data->sprites && data->sprites->next)
		data->sprites = data->sprites->next;
	if (data->sprites)
		data->game[(int)data->sprites->pos.y][(int)data->sprites->pos.x] = '0';
}

void	move_player2(double speed, t_data *data)
{
	if (data->player.gun > 6)
	{
		data->keys.shoot = 0;
		data->player.gun = 0;
		shoot(data);
	}
	if (data->keys.run)
		speed *= 1.8;
	if (data->keys.forward)
		change_p_pos(data, data->player.angle, speed);
	if (data->keys.backward)
		change_p_pos(data, data->player.angle - 180, speed);
	if (data->keys.move_left)
		change_p_pos(data, data->player.angle - 90, speed);
	if (data->keys.move_right)
		change_p_pos(data, data->player.angle + 90, speed);
	if (data->keys.look_left)
		data->player.angle -= 3 + data->keys.run;
	if (data->keys.look_right)
		data->player.angle += 3 + data->keys.run;
}

void	move_player(t_data *data)
{
	double			speed;
	int				crouch;

	speed = 0.3;
	crouch = 0;
	if (data->keys.crouch)
	{
		crouch = -50;
		speed /= 2;
	}
	if (sin(data->player.jump) < 0)
	{
		data->player.jump = 0;
		data->keys.jump = 0;
	}
	if (data->keys.jump == 1)
		data->player.jump += sin(PI / 15);
	if (data->keys.shoot == 1)
		data->player.gun += 0.5;
	move_player2(speed, data);
	data->player.h = data->r.y / 2 + crouch + (sin(data->player.jump) * 100);
}
