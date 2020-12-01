/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:27:19 by magostin          #+#    #+#             */
/*   Updated: 2020/12/01 12:59:55 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		detect_dir(double f, t_data *data)
{
	data->player.dir = -1;
	if (f >= 0 && f < 90)
		data->player.dir = EAST;
	else if (f >= 90 && f < 180)
		data->player.dir = SOUTH;
	else if (f >= 180 && f < 270)
		data->player.dir = WEST;
	else
		data->player.dir = NORTH;
}

t_point		intersect(t_point b, t_point a, t_point c, t_point d)
{
	double	denom;
	t_point	inter;

	denom = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) *
	(c.x - d.x);
	inter.x = ((a.x * b.y - a.y * b.x) * (c.x - d.x) -
	(a.x - b.x) * (c.x * d.y - c.y * d.x)) / denom;
	inter.y = ((a.x * b.y - a.y * b.x) * (c.y - d.y) -
	(a.y - b.y) * (c.x * d.y - c.y * d.x)) / denom;
	return (inter);
}

t_block		closest_wall_a(double f, t_point p, t_block wall, t_data *data)
{
	t_point		a;

	if (data->bounced == 0)
		data->sprites = NULL;
	detect_dir(f, data);
	wall.pos.x = (int)p.x;
	wall.pos.y = (int)p.y;
	while (((int)wall.pos.x >= 0 && (int)wall.pos.y >= 0
	&& (int)wall.pos.y < (int)data->game_size.x
	&& (int)wall.pos.x < (int)data->game_size.y
	&& !ft_strchr("13", data->game[(int)wall.pos.y][(int)wall.pos.x])))
	{
		if (data->game[(int)wall.pos.y][(int)wall.pos.x] == '2')
			sprite_push_front(&data->sprites, new_sprite(wall.pos, data));
		wall.texture = wall_dir(f, p, wall.pos, data);
		wall.pos = change_wall_pos(wall);
	}
	a.x = p.x + cos(ator(f));
	a.y = p.y + sin(ator(f));
	wall.inter = wall_inter(wall, p, a);
	wall.dist += get_dist(p, wall.inter);
	return (wall);
}

void		closest_wall(int x, t_data *data)
{
	double		f;
	t_block		wall;

	data->ray_bounced[x].x = -1;
	f = fix_angle(xtoa(x, data));
	wall.dist = 0;
	wall = closest_wall_a(f, data->player.pos, wall, data);
	data->ray_inter[x] = wall.inter;
	data->distance[x] = wall.dist;
	data->y = ((data->r.x / 2 - data->fov)) / (wall.dist * cos(
	ator(fix_angle(f - data->player.angle))));
	while (game(wall.pos, data) == '3' && data->bounced < 10)
	{
		data->bounced++;
		if (wall.texture == EAST || wall.texture == WEST)
			f = fix_angle(180 - f);
		else
			f = fix_angle(-f);
		wall.inter.x += cos(ator(f)) * 0.001;
		wall.inter.y += sin(ator(f)) * 0.001;
		wall = closest_wall_a(f, wall.inter, wall, data);
		data->ray_bounced[x] = wall.inter;
	}
	draw_wall(x, wall, data);
	draw_sprite(x, data->sprites, data);
}
