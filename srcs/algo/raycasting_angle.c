/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_angle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 16:27:19 by magostin          #+#    #+#             */
/*   Updated: 2020/10/15 01:23:37 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double			xtoa(int x, t_data *data)
{
	return ((data->player.angle + (((double)x / data->r.x - 1) * (double)data->fov) + (data->fov / 2)));
}

double			rtoa(double rad)
{
	return (rad * 180/PI);
}

double			ator(double a)
{
	return (a * PI/180);
}

/*
** Detect player direction based on angle
*/
void			detect_dir(double f, t_data *data)
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

char			wall_dir(double f, t_point p_pos, t_point wall, t_data *data)
{
	double		ang;

	//printf("%f %f\t%f %f\n", p_pos.x, p_pos.y, wall.x, wall.y);
	if (data->player.dir == EAST)
	{
		ang = fix_angle(rtoa(atan2(wall.y - p_pos.y + 1, wall.x - p_pos.x + 1)));
		//printf("%f <= %f\t", f, ang);
		if (f <= ang)
			return (EAST);
		return (SOUTH);
	}
	if (data->player.dir == SOUTH)
	{
		ang = fix_angle(rtoa(atan2(wall.y - p_pos.y + 1, wall.x - p_pos.x)));
		//printf("%f <= %f\t", f, ang);
		if (f <= ang)
			return (SOUTH);
		return (WEST);
	}
	if (data->player.dir == WEST)
	{
		ang = fix_angle(rtoa(atan2(wall.y - p_pos.y, wall.x - p_pos.x)));
		//printf("%f <= %f\t", f, ang);
		if (f <= ang)
			return (WEST);
		return (NORTH);
	}
	if (data->player.dir == NORTH)
	{
		ang = fix_angle(rtoa(atan2(wall.y - p_pos.y, wall.x + 1 - p_pos.x)));
		//printf("%f <= %f\t", f, ang);
		if (f <= ang)
			return (NORTH);
		return (EAST);
	}
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

t_block			closest_wall_a(double f, t_point p, t_block wall, t_data *data);
unsigned int	get_pixel_color(t_point p, double y, t_block wall, t_data *data)
{
	t_texture	t;
	double		ratio_x;
	double		ratio_y;
	double		f;
	int			test;

	f = fix_angle(xtoa(p.x, data));
	t = data->t[wall.texture];
	if (wall.texture == SOUTH || wall.texture == NORTH)
		ratio_x = wall.inter.x - (int)wall.inter.x;
	else
		ratio_x = wall.inter.y - (int)wall.inter.y;
	if (wall.texture == SOUTH || wall.texture == WEST)
		ratio_x = 1 - ratio_x;
	if (ratio_x < 0)
		ratio_x *= -1;
	ratio_y = (p.y - (data->player.h - y)) / (y * 2);
	(void)y;
	test = (int)(t.wth * ratio_x) + (int)(t.lth * ratio_y) * t.wth;
	if (test >= 0 && test < t.wth * t.lth)
		return (t.tab[test]);
	return (WHITE);
}

void		get_texture_a(int x, t_block wall, t_data *data)
{
	double			y;
	double			f;
	int				i;

	f = fix_angle(xtoa(x, data));
	data->distance[x] = wall.dist;
	y = ((data->r.x / 2 - data->fov)) / (wall.dist * cos(ator(fix_angle(f - data->player.angle))));
	i = -1;
	while (++i < data->player.h - data->y)
		draw_pt(x, i, data, data->color[0]);
	if (data->bounced > 0)
		data->mirrored = 1;
	i--;
	while (++i < data->player.h - y)
		draw_pt(x, i, data, data->color[0]);
	while (i >= data->player.h - y && i < (int)(data->player.h) + y)
	{
		draw_pt(x, i, data, get_pixel_color(point(x, i), y, wall, data));
		i++;
	}
	i--;
	while (++i >= (int)(data->player.h) + y && i < (int)(data->player.h) + data->y)
		draw_pt(x, i, data, data->color[1]);
	if (data->bounced > 0)
		data->mirrored = 0;
	i--;
	while (++i < data->r.y)
		draw_pt(x, i, data, data->color[1]);
}

/*
** closest_wall_angle(int x, t_data *data)
*/
t_block		closest_wall_a(double f, t_point p, t_block wall, t_data *data)
{
	t_point		a;
	int			first;

	first = 1;
	data->sprites = NULL;
	detect_dir(f, data);
	wall.pos.x = (int)p.x;
	wall.pos.y = (int)p.y;
	while (((int)wall.pos.x >= 0 && (int)wall.pos.y >= 0 && (int)wall.pos.y < (int)data->game_size.x && (int)wall.pos.x < (int)data->game_size.y && !ft_strchr("13", data->game[(int)wall.pos.y][(int)wall.pos.x])))
	{
		first--;
		if (data->game[(int)wall.pos.y][(int)wall.pos.x] == '2')
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

void		closest_wall_angle(int x, t_data *data)
{
	double		f;
	t_block		wall;

	data->mirrored = 0;
	data->bounced = 0;
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
		{
			f = fix_angle(180 - f);
			wall.inter.x += cos(ator(f)) * 0.001;
			wall.inter.y += sin(ator(f)) * 0.001;
			wall = closest_wall_a(f, wall.inter, wall, data);
		}
		else if (wall.texture == NORTH)
		{
			f = fix_angle(-f);
			wall.inter.x += cos(ator(f)) * 0.001;
			wall.inter.y += sin(ator(f)) * 0.001;
			wall = closest_wall_a(f, wall.inter, wall, data);
		}
		else if (wall.texture == SOUTH)
		{
			f = fix_angle(-f);
			wall.inter.x += cos(ator(f)) * 0.001;
			wall.inter.y += sin(ator(f)) * 0.001;
			wall = closest_wall_a(f, wall.inter, wall, data);
		}
		data->ray_bounced[x] = wall.inter;
	}
	get_texture_a(x, wall, data);
	draw_height_sprite(x, data->sprites, data);
	data->mirrored = 0;
}