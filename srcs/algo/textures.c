/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:10:15 by magostin          #+#    #+#             */
/*   Updated: 2020/11/28 15:22:22 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_pixel		get_pixel_color(t_point p, double y, t_block wall, t_data *data)
{
	t_texture	t;
	double		ratio_x;
	double		ratio_y;
	double		f;
	int			color;

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
	color = (int)(t.wth * ratio_x) + (int)(t.lth * ratio_y) * t.wth;
	return (fog_color(t.tab[color], data->distance[(int)p.x], data));
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
	data->mirrored = 0;
	while (++i < data->player.h - y)
	{
		if (data->mirrored == 0 && i >= data->player.h - data->y)
			data->mirrored = 1;
		draw_pt(x, i, data, data->color[0]);
	}
	i--;
	while (++i >= data->player.h - y && i < (int)(data->player.h) + y)
		draw_pt(x, i, data, get_pixel_color(point(x, i), y, wall, data));
	i--;
	data->mirrored = 1;
	while (++i < data->r.y)
	{
		if (data->mirrored && i >= (int)(data->player.h) + data->y)
			data->mirrored = 0;
		draw_pt(x, i, data, data->color[1]);
	}
}
