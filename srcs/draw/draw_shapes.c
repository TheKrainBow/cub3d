/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 02:56:53 by magostin          #+#    #+#             */
/*   Updated: 2020/10/09 04:48:15 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** draw a point on the screen
*/
void		draw_pt(int x, int y, t_data *data, unsigned int color)
{
	if (y >= 0 && y < data->r.y && x >= 0 && x < data->r.x && color)
		data->draw[(y * (int)data->r.x) + x]
		= data->average ? average_color(data->draw[(y * (int)data->r.x) + x], color, 0.3) : color;
}

/*
** draw a line on the screen
*/
void		draw_line(t_point a, t_point b, t_data *data, unsigned int color)
{
	int			i;
	t_point		d;
	double		steps;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	steps = fabs(d.x) > fabs(d.y) ? fabs(d.x) : fabs(d.y);

	d.x /= steps;
	d.y /= steps;
	i = -1;
	while (++i <= steps)
	{
		draw_pt(a.x, a.y, data, color);
		a.x = a.x + d.x;
		a.y = a.y + d.y;
	}
}

/*
** draw a circle on the screen
*/
void		draw_circle(t_point center, int radius, t_data *data, unsigned int color)
{
	double		i;
	t_point		a;
	t_point		b;

	i = 0;
	while (i < 360)
	{
		a.x = center.x + (cos(i * PI / 180) * radius);
		a.y = center.y + (sin(i * PI / 180) * radius);
		b.x = center.x + (cos((i + 1) * PI / 180) * radius);
		b.y = center.y + (sin((i + 1) * PI / 180) * radius);
		draw_line(a, b, data, color);
		i += 0.5;
	}
}

/*
** draw a square on the screen
*/
void		draw_square(t_point p, double size, unsigned int color, t_data *data)
{
	int		i;
	int		j;

	p.x += 0.5;
	p.x *= MULT;
	p.y += 0.5;
	p.y *= MULT;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			draw_pt(p.x + i - (size / 2), p.y + j - (size / 2), data, color);
	}
}

/*
** Put all pixels of the screen in a given color
*/
void		clear_screen(unsigned int color, t_data *data)
{
	int		i;

	i = -1;
	while (++i < (int)data->r.x * (int)data->r.y)
		data->draw[i] = color;
}