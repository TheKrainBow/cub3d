/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:22:04 by magostin          #+#    #+#             */
/*   Updated: 2020/11/29 23:50:17 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "struct.h"

double	map(double i, t_point range1, t_point range2)
{
	double		ratio;

	range1.y -= range1.x;
	i -= range1.x;
	ratio = i / range1.y;
	range2.y -= range2.x;
	return (range2.y * ratio + range2.x);
}

void	draw_gun(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	t_pixel	color;

	i = data->r.x / 3 - 1;
	while (++i < data->r.x)
	{
		j = data->r.y / 5 - 1;
		while (++j < data->r.y)
		{
			x = (int)map(i, point(0, data->r.x),
			point(0, data->gun[(int)data->player.gun].wth));
			y = (int)map(j, point((int)(data->r.y / 5), data->r.y),
			point(0, data->gun[(int)data->player.gun].lth));
			color = data->gun[(int)data->player.gun].tab[x + y * data->
			gun[(int)data->player.gun].wth];
			draw_pt(i, j, data, color);
		}
	}
}

void	draw_hp(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	t_pixel	color;

	i = 0;
	while (++i < data->r.x / 2)
	{
		j = 3 * data->r.y / 4;
		while (++j < data->r.y)
		{
			x = (int)map(i, point(0, data->r.x / 2),
			point(0, data->health.wth));
			y = (int)map(j, point(3 * data->r.y / 4, data->r.y),
			point(0, data->health.lth));
			color = data->health.tab[x + y * data->health.wth];
			draw_pt(i, j, data, color);
		}
	}
}

void	draw_hud(t_data *data)
{
	if (data->keys.open_map)
		draw_map(data);
	draw_gun(data);
	draw_hp(data);
	draw_crosshair(data->r.x / 40, data);
}

void	draw_map(t_data *data)
{
	t_point	p;

	p.y = -1;
	data->average = 1;
	while (++p.y < data->game_size.x)
	{
		p.x = -1;
		while (++p.x < data->game_size.y)
		{
			if (ft_strchr("0NSEW2", data->game[(int)p.y][(int)p.x]))
				draw_square(p, data->mult * 0.9, pixel(20, 20, 20, 1), data);
			if (data->game[(int)p.y][(int)p.x] == '1')
				draw_square(p, data->mult * 0.9, pixel(80, 80, 80, 1), data);
		}
	}
	data->average = 0;
	draw_player_map(data);
}

void	draw_player_map(t_data *data)
{
	int		x;
	t_point	a;
	t_point	b;
	t_point	temp;
	double	f;

	temp.x = data->player.pos.x * data->mult;
	temp.y = data->player.pos.y * data->mult;
	x = data->r.x / 2;
	f = (x * data->fov) / (data->r.x - 1);
	a.x = data->ray_inter[x].x * data->mult;
	a.y = data->ray_inter[x].y * data->mult;
	if (x < 20 || x > data->r.x - 20)
		draw_line(temp, a, data, pixel(0, 0, 255, 1));
	else
		draw_line(temp, a, data, pixel(255, 255, 255, 1));
	if (data->ray_bounced[x].x != -1)
	{
		a.x = data->ray_inter[x].x * data->mult;
		a.y = data->ray_inter[x].y * data->mult;
		b.x = data->ray_bounced[x].x * data->mult;
		b.y = data->ray_bounced[x].y * data->mult;
		if (get_dist(a, b) < 1000)
			draw_line(a, b, data, pixel(0, 255, 0, 1));
	}
	x++;
	draw_circle(temp, 2, data, pixel(255, 255, 255, 1));
}

void	draw_crosshair(int size, t_data *data)
{
	int		i;
	t_point	center;
	t_point	p1;
	t_point	p2;

	i = -1;
	while (++i <= 1)
	{
		p1.x = data->r.x / 2 - (size * i);
		p1.y = data->r.y / 2 - (size * !i);
		p2.x = data->r.x / 2 + (size * i);
		p2.y = data->r.y / 2 + (size * !i);
		draw_line(p1, p2, data, pixel(255, 255, 255, 1));
	}
	center.x = data->r.x / 2;
	center.y = data->r.y / 2;
	draw_circle(center, size / 2, data, pixel(255, 255, 255, 1));
}
