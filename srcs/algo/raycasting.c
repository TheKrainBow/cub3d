/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:27:19 by magostin          #+#    #+#             */
/*   Updated: 2020/11/28 15:52:50 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

double		wall_dir_return(int y, int x, t_point wall, t_point p_pos)
{
	return (fix_angle(rtoa(atan2(wall.y - p_pos.y + y, wall.x - p_pos.x + x))));
}

char		wall_dir(double f, t_point p_pos, t_point wall, t_data *data)
{
	if (data->player.dir == EAST)
	{
		if (f <= wall_dir_return(1, 1, wall, p_pos))
			return (EAST);
		return (SOUTH);
	}
	if (data->player.dir == SOUTH)
	{
		if (f <= wall_dir_return(1, 0, wall, p_pos))
			return (SOUTH);
		return (WEST);
	}
	if (data->player.dir == WEST)
	{
		if (f <= wall_dir_return(0, 0, wall, p_pos))
			return (WEST);
		return (NORTH);
	}
	if (data->player.dir == NORTH)
		if (f <= wall_dir_return(0, 1, wall, p_pos))
			return (NORTH);
	return (EAST);
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

t_point		point(double x, double y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_block		closest_wall_a(double f, t_point p, t_block wall, t_data *data)
{
	t_point		a;
	int			first;

	first = 1;
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
		first--;
		if (data->bounced == 0 && data->game[(int)wall.pos.y][(int)wall.pos.x] == '2')
			sprite_push_front(&data->sprites, new_sprite(wall.pos, data));
		wall.texture = wall_dir(f, p, wall.pos, data);
		if (wall.texture == NORTH)
			wall.pos.y--;
		if (wall.texture == SOUTH)
			wall.pos.y++;
		if (wall.texture == WEST)
			wall.pos.x--;
		if (wall.texture == EAST)
			wall.pos.x++;
	}
	a.x = p.x + cos(ator(f));
	a.y = p.y + sin(ator(f));
	wall.inter =
	intersect(
	p,
	a,
	point(wall.pos.x + (wall.texture == WEST), wall.pos.y + (wall.texture == NORTH)),
	point(wall.pos.x + (wall.texture != EAST), wall.pos.y + (wall.texture != SOUTH)));
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
	data->y = ((data->r.x / 2 - data->fov)) / (wall.dist * cos(ator(fix_angle(f - data->player.angle))));
	while (data->game[(int)wall.pos.y][(int)wall.pos.x] == '3' && data->bounced < 3)
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
