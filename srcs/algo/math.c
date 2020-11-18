/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 03:28:00 by magostin          #+#    #+#             */
/*   Updated: 2020/11/11 18:29:11 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** get the distance between two points
*/
double			get_dist(t_point a, t_point b)
{
	return (hypotf(a.x - b.x, a.y - b.y));
}

/*
** get the intersection point between a segment and an sprite
*/
t_point			get_inter(t_point b, t_point a, t_sprite *obj)
{
	double		t;
	double		u;
	double		denum;
	t_point		c;
	t_point		d;
	t_point		inter;

	c = obj->p[0];
	d = obj->p[1];
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
		}
	}
	return (inter);
}

/*
** Check if a point coordinates are valid for the current map
*/
int				check_point(t_point p, t_data *data)
{
	if (p.x >= 0 && p.x < data->game_size.y && p.y >= 0 && p.y < data->game_size.x)
		return (1);
	return (0);
}
