/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:09 by magostin          #+#    #+#             */
/*   Updated: 2020/08/06 05:07:00 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include "cub3D.h"

void		draw_pt(int x, int y, t_data *data, unsigned int color)
{
	data->draw[(y * (int)data->r.x) + x] = color;
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
	while (data->walls[++i].p[0].x != -42)
	{
		a.x = data->walls[i].p[0].x * mult;
		a.y = data->walls[i].p[0].y * mult;
		b.x = data->walls[i].p[1].x * mult;
		b.y = data->walls[i].p[1].y * mult;
		draw_line(a, b, data, data->walls[i].color);
	}
}

void		draw_line(t_point a, t_point b, t_data *data, unsigned int color)
{
	int		i;
	t_point	temp;

	/*i = -1;
	while (b.x - a.x > b.y - a.y && (++i < b.x - a.x))
		draw_pt(i + a.x, a.y + (i * (b.y - a.y)) / (b.x - a.x), data, color);*/
	i = -1;
	while (/*b.x - a.x <= b.y - a.y && */(++i < b.y - a.y))
		draw_pt(a.x + (i * (b.x - a.x)) / (b.y - a.y), i + a.y, data, color);
}

void		draw_circle(t_point center, int radius, t_data *data)
{
	double i;
	/*t_point a;
	t_point b;*/

	i = 0;
	while (i < 360)
	{
		/*a.x = center.x + (cos(i * PI / 180) * radius);
		a.y = center.y + (sin(i * PI / 180) * radius);
		b.x = center.x + (cos((i + 1) * PI / 180) * radius);
		b.y = center.y + (sin((i + 1) * PI / 180) * radius);*/
		draw_pt(center.x + (cos(i * PI / 180) * radius), center.y + (sin(i * PI / 180) * radius), data, WHITE);
		i += 1;
	}
}

t_point			get_intersect(t_point b, t_point a, t_wall wall)
{
	double		t;
	double		u;
	double		denum;
	t_point		c;
	t_point		d;
	t_point		inter;

	c = wall.p[0];
	d = wall.p[1];
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

void		get_texture(t_point a, t_point b, t_data *data, t_wall wall)
{
	int			i;
	t_point		temp;
	double		col;

	if (wall.color == NORTH || wall.color == SOUTH)
		col = (int)(wall.t->lth * ((wall.inter.y - wall.p[0].y)));
	else
		col = (int)(wall.t->lth * ((wall.inter.x - wall.p[0].x)));
	i = -1;
		while ((++i < b.y - a.y))
			if (a.x + (i * (b.x - a.x)) / (b.y - a.y) < data->r.x && a.x + (i * (b.x - a.x)) / (b.y - a.y) > 0 && i + a.y < data->r.y && i + a.y > 0)
				draw_pt(a.x + (i * (b.x - a.x)) / (b.y - a.y), i + a.y, data, wall.t->tab[(int)(col) + (wall.t->lth * (int)(i * (wall.t->lth / (b.y - a.y))))]);
}

double			get_angle(t_point a, t_point player)
{
	return ((acosf((a.x - player.x) / get_dist(a, player)) * (180/PI)) < 0
	? (acosf((a.x - player.x) / get_dist(a, player)) * (180/PI))
	: (asinf((a.y - player.y) / get_dist(a, player))) * (180/PI));
}

int			closest_wall(t_point x, t_data *data)
{
	int			i;
	int			best;
	int			dist;

	i = -1;
	best = -1;
	while (data->walls[++i].p[0].x != -42)
	{
		data->walls[i].inter = get_intersect(data->player.pos, x, data->walls[i]);
		data->walls[i].inter.dist = get_dist(data->player.pos, data->walls[i].inter);
		if ((best == -1 || data->walls[i].inter.dist <= data->walls[best].inter.dist) && (data->walls[i].inter.x && data->walls[i].inter.y))
			best = i;
	}
	return (best);
}

void			draw_height(double angle, t_wall wall, t_data *data)
{
	t_point a;
	t_point b;

	a.x = ((angle/* - (data->player.angle + (FOV / 2))*/) / FOV) * (int)data->r.x;
	b.x = a.x;
	a.y = (int)data->r.y/2 + (((int)data->r.y/2 / wall.inter.dist));
	b.y = (int)data->r.y/2 - (((int)data->r.y/2 / wall.inter.dist));
	get_texture(b, a, data, wall);
}

void			draw_screen(t_data *data)
{
	int			i;
	double		f;
	double			angle;
	int			j;
	t_point		a;
	int			closest;


	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 20)
		{
			data->test[i][j] = ' ';
			j++;
		}
		data->test[i][j] = 0;
		i++;
	}
	f = 0;
	while (f < FOV && data->toggle == 1)
	{
		closest_wall_dda(f, data);
		//f++;
		f += (double)FOV / 2000;
	}

	f = 0;
	while (f < FOV && data->toggle == 0)
	{
		a.x = data->player.pos.x + (cosf((data->player.angle - (FOV / 2) + f) * (PI / 180)));
		a.y = data->player.pos.y + (sinf((data->player.angle - (FOV / 2) + f) * (PI / 180)));
		closest = closest_wall(a, data);
		draw_height(f, data->walls[closest], data);
		f += (double)FOV / 2000;
	}
	f = 0;
	printf("\n\n\n\n\n");
	while ((int)f < 11)
	{
		printf("%s\n", data->test[(int)f]);
		f++;
	}
	/*i = -1;
	while (data->walls[++i].p[0].x != -42)
	{
		j = -1;
		while (++j < 2)
		{
			angle = get_angle(data->walls[i].p[j], data->player.pos);
			if ((int)angle >= ((int)data->player.angle - (FOV / 2)) && (int)angle <= ((int)data->player.angle + (FOV / 2)))
			{
				a.x = data->walls[i].p[j].x;
				a.y = data->walls[i].p[j].y;
				closest = closest_wall(a, data);
				draw_height(-((data->player.angle + (FOV / 2)) - angle), data->walls[closest], data);
			}
		}
	}*/
}