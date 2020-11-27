/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 04:53:01 by magostin          #+#    #+#             */
/*   Updated: 2020/11/26 17:28:08 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** convert a string to an int
*/
int		ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
	|| str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * neg);
}

/*
** Fix the angle to be between 0 and 360
*/
double		fix_angle(double ang)
{
	while (ang < (double)0)
		ang += 360;
	while (ang >= (double)360)
		ang -= 360;
	return (ang);
}

void		change_p_pos(t_data *data, double angle, double speed)
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

t_block		closest_wall_a(double f, t_point p, t_block wall, t_data *data);
void		shoot(t_data *data)
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

void		move_player(t_data *data)
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
		data->player.jump += sin(PI/15);
	if (data->keys.shoot == 1)
		data->player.gun += 0.5;
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
	data->player.h = data->r.y / 2 + crouch + (sin(data->player.jump) * 100);
}