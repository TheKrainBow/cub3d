/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:09 by magostin          #+#    #+#             */
/*   Updated: 2020/10/02 21:57:59 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		draw_pt(int x, int y, t_data *data, unsigned int color)
{
	if (y > 0 && y < data->r.y && x > 0 && x < data->r.x && color)
	{
		data->draw[(y * (int)data->r.x) + x] = color;
	}
}

double			get_dist(t_point a, t_point b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

void		draw_walls(t_data *data, int mult)
{
	int			i;
	t_point		a;
	t_point		b;

	i = -1;
	while (++i < data->n_objs)
	{
		a.x = data->objs[i].p[0].x * mult;
		a.y = data->objs[i].p[0].y * mult;
		b.x = data->objs[i].p[1].x * mult;
		b.y = data->objs[i].p[1].y * mult;
		draw_line(a, b, data, data->objs[i].color);
	}
}

void		draw_line(t_point a, t_point b, t_data *data, unsigned int color)
{
	int			i;
	double		x,y;
	int			dx, dy;
	int			steps;
	double		xinc, yinc;

	dx = b.x - a.x;
	dy = b.y - a.y;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	xinc = dx / (double)steps;
	yinc = dy / (double)steps;
	x = a.x;
	y = a.y;
	i = -1;
	while (++i <= steps)
	{
		draw_pt(x, y, data, color);
		x += xinc;
		y += yinc;
	}
}

void		draw_circle(t_point center, int radius, t_data *data, unsigned int color)
{
	double i;
	/*t_point a;
	t_point b;*/
	center.x *= MULT;
	center.y *= MULT;

	i = 0;
	while (i < 360)
	{
		/*a.x = center.x + (cos(i * PI / 180) * radius);
		a.y = center.y + (sin(i * PI / 180) * radius);
		b.x = center.x + (cos((i + 1) * PI / 180) * radius);
		b.y = center.y + (sin((i + 1) * PI / 180) * radius);*/
		draw_pt(center.x + (cos(i * PI / 180) * radius), center.y + (sin(i * PI / 180) * radius), data, color);
		i += 1;
	}
}

t_point			get_intersect(t_point b, t_point a, t_object obj)
{
	double		t;
	double		u;
	double		denum;
	t_point		c;
	t_point		d;
	t_point		inter;

	c = obj.p[0];
	d = obj.p[1];
	denum = ((a.x - b.x) * (c.y - d.y)) - ((a.y - b.y) * (c.x - d.x));
	t = (((a.x - c.x) * (c.y - d.y)) - ((a.y - c.y) * (c.x - d.x)));
	u = -(((a.x - b.x) * (a.y - c.y)) - ((a.y - b.y) * (a.x - c.x)));
	inter.x = 0;
	inter.y = 0;
	if (denum != 0)
	{
		t /= denum;
		u /= denum;
		if ((t <= 1) && (0 <= u && u <= 1))
		{
			inter.x = a.x + (t * (b.x - a.x));
			inter.y = a.y + (t * (b.y - a.y));
			return (inter);
		}
	}
	return (inter);
}

void		get_texture(int y, double angle, t_data *data, t_object obj)
{
	int				i;
	int				x;
	t_point			temp;
	double			col;
	unsigned int	color;

	x = (((angle / data->fov) * data->r.x));
	if (obj.color == NORTH || obj.color == SOUTH)
		col = ((double)obj.t->wth * ft_sub_abs(obj.inter.y, obj.p[0].y));
	else
		col = ((double)obj.t->wth * ft_sub_abs(obj.inter.x, obj.p[0].x));
	i = -1;
	while ((++i < data->r.y))
	{
		if (i <= y)
			draw_pt(x, i, data, data->color[0]);
		else if (i > y && i < ((int)data->r.y - y))
		{
			color = obj.t->tab[(int)(((int)col % obj.t->wth) + (((i - y) * ((int)obj.t->lth) / ((int)data->r.y - y - y)) * ((int)obj.t->wth)))];
			draw_pt(x, i, data, color);
		}
		else
			draw_pt(x, i, data, data->color[1]);
	}
}

double			get_angle(t_point a, t_point player)
{
	return ((acosf((a.x - player.x) / get_dist(a, player)) * (180/PI)) < 0
	? (acosf((a.x - player.x) / get_dist(a, player)) * (180/PI))
	: (asinf((a.y - player.y) / get_dist(a, player))) * (180/PI));
}

void			draw_height(double angle, t_object obj, t_data *data, int i)
{
	int y;

	y = (int)data->r.y/2 - (((int)(data->r.y / 2) / (obj.inter.dist)));
	get_texture(y, angle, data, obj);
}

void			draw_sprites(double f, int best_wall, t_data *data)
{
	t_point	start;
	double	angle;
	int		i;
	double	a;
	double	b;

	start = data->objs[best_wall].inter;
	angle = (data->player.angle - data->fov/2 + f);
	a = (start.y - data->player.pos.y) / (start.x - data->player.pos.x);
	b = start.y - a * start.x;
	draw_circle(start, 5, data, EAST);
	draw_pt(start.x * MULT, start.y * MULT, data, EAST);
	draw_circle(data->player.pos, 5, data, WHITE);
	round_angle(&angle);
	/*printf("y = a * x + b\n");
	printf("y = %f * x + %f\n", a, b);
	printf("x = (y - b) / a\n");
	printf("x = (y - %f) / %f\n", a, b);*/
	i = -1;
	start.x = (int)start.x;
	start.y = a * start.x + b;
	while ((data->objs[best_wall].inter.x - data->player.pos.x) * (start.x - data->player.pos.x) > 0)
	{
		if ((data->objs[best_wall].inter.x - data->player.pos.x) * (start.x - data->player.pos.x) > 0)
			draw_circle(start, 2, data, 0xFF0000);
		start.x += (start.x - data->player.pos.x) >= 0 ? -1 : 1;
		start.y = a * start.x + b;
	}
	start = data->objs[best_wall].inter;
	start.y = (int)start.y;
	start.y = a * start.x + b;
	i = -1;
	while ((data->objs[best_wall].inter.y - data->player.pos.y) * (start.y - data->player.pos.y) > 0)
	{
		if ((data->objs[best_wall].inter.y - data->player.pos.y) * (start.y - data->player.pos.y) > 0)
			draw_circle(start, 1, data, 0x00FF00);
		start.y += (start.y - data->player.pos.y) >= 0 ? -1 : 1;
		start.x = (start.y - b) / a;
	}
	//printf("%f %f %f\n", start.x, start.y, angle);
}

void			closest_object(double f, t_point x, t_data *data)
{
	int			i;
	int			best_wall;
	int			best_sprite;
	int			dist;

	i = -1;
	best_wall = -1;
	while (++i < data->n_objs)
	{
		data->objs[i].inter = get_intersect(data->player.pos, x, data->objs[i]);
		data->objs[i].inter.dist = get_dist(data->player.pos, data->objs[i].inter);
		if ((best_wall == -1 || data->objs[i].inter.dist <= data->objs[best_wall].inter.dist) && (data->objs[i].inter.x && data->objs[i].inter.y))
			best_wall = i;
	}
	draw_height(f, data->objs[best_wall], data, 0);
	return ;
}

void			draw_grid(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_L)
		{
			if (data->game[i][j] == '0')
				draw_square(j * MULT, i * MULT, MULT - 2, 0x424242, data);
			if (data->game[i][j] == '1')
				draw_square(j * MULT, i * MULT, MULT - 1, 0xAAAAAA, data);
			if (data->game[i][j] == '2')
				draw_square(j * MULT + MULT / 4, i * MULT + MULT / 4, MULT / 2, 0xEEEEEE, data);
		}
	}
}

void			draw_screen(t_data *data)
{
	int			i;
	double		f;
	int			j;
	t_point		a;
	int			closest;

	//draw_grid(data);
	f = 0;
	while (f < data->fov)
	{
		a.x = data->player.pos.x + (cosf((data->player.angle - (data->fov / 2) + f) * (PI / 180)));
		a.y = data->player.pos.y + (sinf((data->player.angle - (data->fov / 2) + f) * (PI / 180)));
		//closest_object(f, a, data);
		//if (f > (FOV/2 - 10) && f < (FOV/2 + 10))
		//if (f == 0)
		//	travel_algo(f, a, data);
		//if (f == 0)
			dda_test(f, data);
		//closest = closest_object(f, a, data);
		//draw_height(f, data->objs[closest], data, 0);
		f += (double)data->fov / (data->r.x + 1);
	}
}